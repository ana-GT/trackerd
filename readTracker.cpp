
#include <sns.h>
#include <unistd.h>
#include <fstream>
#include "tracker_msg.h"

struct timespec t_now;
struct timespec t_timeout;


ach_channel chan;
std::string chan_opt("tracker");

int main( int argc, char* argv[] ) {

  int v;
  while( (v=getopt(argc,argv,"c:h")) != -1 ) {
    switch(v) {
    case 'c': {
      chan_opt.assign(optarg);
    } break;
    case 'h': {
      printf("Syntax: %s -c CHANNEL_NAME \n", argv[0]);
      return 1;
    } break;
    }
  }
  
  // Open channel
  if( ach_open( &chan, chan_opt.c_str(), NULL ) != ACH_OK ) {
    printf("Error opening channel %s \n", chan_opt.c_str() );
    return -1;
  }
  
  // Loop
  std::ofstream output( "test.txt", std::ofstream::out );
  while(true) {

    // Read channel
    if( clock_gettime( ACH_DEFAULT_CLOCK, &t_now ) ) {
      SNS_LOG( LOG_ERR, "clock_gettime failed: '%s' \n", strerror(errno) );
      break;
    }

    t_timeout = sns_time_add_ns( t_now, 1000*1000*1 );

    size_t frame_size;
    void* buf = NULL;
    ach_status_t r;
    r = sns_msg_local_get( &chan, &buf, &frame_size, &t_timeout,
			   ACH_O_LAST | ACH_O_WAIT );
    switch(r) {
    case ACH_OK:
    case ACH_MISSED_FRAME: {
      struct sns_msg_tracker* msg = (struct sns_msg_tracker*)buf;
      sns_msg_tracker_dump( stdout, msg );
      for( int i = 0; i < msg->header.n; ++i ) {
	printf("Writing \n");
	output << msg->u[i].x << " " << msg->u[i].y << " " << msg->u[i].z << " ";
      }
      output <<std::endl;
    } break;
      
    }

    usleep(0.25e6);
  } // end while

  output.close();
  
}
