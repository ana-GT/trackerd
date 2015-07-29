/**
 * @file trackerd.cpp
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <glib.h>

#include "PiTracker.h"
#include "TrackerUnit.h"
#include "trackerd.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <Eigen/Geometry>

#include "tracker_msg.h"

#define BUFFER_SIZE   1000

struct pos {
  float x; float y; float z;
  float qx; float qy; float qz; float qw;
  int id;
};

std::string chan_opt("tracker");
ach_channel chan;

CNX_STRUCT cnxStruct;
CNX_PARAMS cp;
TrackerUnit tu;


void cleanup_tracker(void) {

  cnxStruct.pTrak->CloseTrk();  // close down the tracker connection
  usleep(2000);
  delete cnxStruct.pTrak;
}

/**
 * @function sendMsg
 */
bool sendMsg( BYTE _buf[BUFFER_SIZE] ) {

  // Cast as char*
  std::string text( (char*)_buf );

  // Read lines
  std::vector<pos> values;
  std::stringstream ss( text );
  std::string line;
  
  while( true ) {
    std::getline(ss, line);
    if( ss.eof() ) { break; }
    std::stringstream ss2(line);
    pos p;
    ss2 >> p.id >> p.x >> p.y >> p.z >> p.qw >> p.qx >> p.qy >> p.qz;
    values.push_back(p);
    
  }
  
  // Send msg
  sns_msg_tracker* msg;
  msg = sns_msg_tracker_alloc( values.size() );
  msg->header.n = values.size();
  for( int i = 0; i < msg->header.n; ++i ) {
    msg->u[i].x = values[i].x; msg->u[i].y = values[i].y; msg->u[i].z = values[i].z;
    msg->u[i].qx = values[i].qx; msg->u[i].qy = values[i].qy;
    msg->u[i].qz = values[i].qz; msg->u[i].qw = values[i].qw;
    msg->u[i].id = values[i].id;
  }

  return ( ach_put( &chan, msg, sns_msg_tracker_size( msg ) ) == ACH_OK );
}

/**
 * @function main 
 */
int main(int argc,char* argv[]){

  atexit(cleanup_tracker);
  
  int v;
  while( (v=getopt(argc,argv,"s:t:p:c:h")) != -1 ) {
    switch(v) {
    case 'c': {
      chan_opt.assign( optarg );
    } break;
    case 's': {
      int s = atoi(optarg);
      if( s == 0 ) { cnxStruct.cnxType = RS232_CNX; }
      else { cnxStruct.cnxType = USB_CNX; }
    } break;
    case 't': {
      cnxStruct.trackerType=atoi(optarg);      
    } break;
    case 'p': {
      g_strlcpy( cp.port, optarg, 50 );
    } break;
    case 'h': {
      printf("Syntax: %s -c CHAN_NAME -s COMM_TYPE -t TRACKER_TYPE -p PORT \n", argv[0]);
      printf("\t COMM_TYPE: 0=RS232 1=USB \n");
      printf("\t TRACKER_TYPE: 0=LIBERTY_HS \n");
      printf("\t PORT: i.e. /dev/ttyS0 \n");
      return -1;
    } break;
    } // end switch
  }

  // Open channel
  ach_status r; r = ach_open( &chan, chan_opt.c_str(), NULL );
  if( r != ACH_OK ) {
    printf("Error openning channel %s \n", chan_opt.c_str() );
    return -2;
  }
  

  if( tu.InitTrackerUnit(BUFFER_SIZE) < 0 ) {
    fprintf(stderr,"Memory Allocation Error setting up buffers\n");
    return -1;
  }

  // The communication with the tracker
  cnxStruct.pTrak = new PiTracker;
  if ( !cnxStruct.pTrak ) {
    printf("Memory Allocation Error creating tracker communications module\n");
    return -3;
  }
  
  // Create connection
  if( !connect( &cnxStruct, cp ) ) {
    printf( "Could not create connection USB. Exiting \n");
    return -3;
  }

  // Start reading
  BYTE buf[BUFFER_SIZE];
  int len=0;
  int bw;
  
  // first establish comm and clear out any residual trash data
  do {
    cnxStruct.pTrak->WriteTrkData( (void*)"\r",1);  // send just a cr, should return an short "Invalid Command" response
    usleep(100000);
    len=cnxStruct.pTrak->ReadTrkData(buf,BUFFER_SIZE);  // keep trying till we get a response
  } while (!len);


  // CONFIGURATION
  int key_return;
  key_return = 0xFF0D;
  
  // Set units in cm  
  cnxStruct.pTrak->WriteTrkData( (void*)"U1",2);
  cnxStruct.pTrak->WriteTrkData(&key_return, 1);
  usleep(100000);
  // x,y,z and quaternion, return carriage
  cnxStruct.pTrak->WriteTrkData( (void*)"O*,2,7,1",8);
  cnxStruct.pTrak->WriteTrkData(&key_return, 1);
  usleep(100000);
  
  // Loop
  while (true){

    // Write command
    cnxStruct.pTrak->WriteTrkData( (void*)"p",1);
    usleep(100000);
    len=cnxStruct.pTrak->ReadTrkData(buf,BUFFER_SIZE);  

    if (len>0 && len<BUFFER_SIZE){
      buf[len]=0;  // null terminate
      do {
	bw=tu.WritePP(buf,len);  // write to buffer
	usleep(1000);
      }while(!bw);
    }

    // Read buffer and publish on terminal
    len = tu.ReadPP(buf);
    while(len) {
      buf[len] = 0;
      len = tu.ReadPP(buf);
      if( !sendMsg(buf) ) { printf("Error sending to channel \n"); return -1; };
    }

    usleep(10000);  // rest for 10ms
  }

  return 0;

}




/**
 * 
 * @brief Connect to the tracker and start the read thread and write timeout
 */
bool connect( LPCNX_STRUCT _pcs, 
	      CNX_PARAMS _cp ){

  int cnxSuccess;
  char* str;
  
  // USB
  if( _pcs->cnxType==USB_CNX ){
    do {
      cnxSuccess=_pcs->pTrak->UsbConnect( usbTrkParams[_pcs->trackerType].vid,
					  usbTrkParams[_pcs->trackerType].pid,
					  usbTrkParams[_pcs->trackerType].writeEp,
					  usbTrkParams[_pcs->trackerType].readEp );       
    } while (cnxSuccess!=0);

    printf("Connected to %s over USB \n", trackerNames[_pcs->trackerType] );
  }
  // RS232
  else { 
    cnxSuccess=_pcs->pTrak->Rs232Connect(_cp.port);
    if (cnxSuccess!=0){
      printf( "Unable to connect to RS232 port %s \n",_cp.port );
      return false;
    }
    printf("Connected over RS232 at port %s",_cp.port );
  }

  return true;
}



