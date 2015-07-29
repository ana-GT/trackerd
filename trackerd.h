/**
 * @file trackerd.h
 * @brief Heavily based on PiTerm.h
 */

#pragma once

enum{TRKR_LIB_HS,TRKR_LIB,TRKR_PAT_HS,TRKR_PAT,TRKR_FT,TRKR_FT3,NUM_SUPP_TRKS};

// Message

// structure definitions

typedef struct _CNX_PARAMS {
  int cnxType;
  int tracker;
  char port[50];
}*LPCNX_PARAMS,CNX_PARAMS;

typedef struct _CNX_STRUCT {
  int cnxType;
  int trackerType;
  PiTracker* pTrak;
}*LPCNX_STRUCT,CNX_STRUCT;

typedef struct _USB_PARAMS {
  int vid;
  int pid;
  int writeEp;
  int readEp;
}*LPUSB_PARAMS,USB_PARAMS;


// usb vid/pids for Polehemus trackers
USB_PARAMS usbTrkParams[NUM_SUPP_TRKS]={
  {0x0f44,0xff20,0x04,0x88},  // Lib HS
  {0x0f44,0xff12,0x02,0x82},   // Lib
  {0X0f44,0xef20,0x04,0x88},  // Patriot HS
  {0x0f44,0xef12,0x02,0x82},  // Patriot
  {0x0f44,0x0002,0x02,0x82},	// Fastrak
  {0x0f44,0x0003,0x02,0x84}};  // Fastrak 3

// polhemus tracker names
const char* trackerNames[NUM_SUPP_TRKS]={
  "High Speed Liberty","Liberty","High Speed Patriot","Patriot","Fastrak","Fastrak 3"};

bool connect( LPCNX_STRUCT _pcs,
	      CNX_PARAMS _cp );
