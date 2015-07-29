// PiTracker.h


/*
Polhemus Tracker Terminal(PiTerm) version 1.0.3 -- Terminal Interface to Polhemus Trackers: Fastrak, Patriot, and Liberty
Copyright  ©  200-2011  Polhemus, Inc.

This file is part of Tracker Terminal.

Tracker Terminal is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tracker Terminal is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tracker Terminal.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************


*/



#ifndef PITRACKER_H_
#define PITRACKER_H_

#define BYTE unsigned char
#include <libusb-1.0/libusb.h>
#include <termios.h>

enum{NO_CNX=-1,USB_CNX,RS232_CNX};


class PiTracker {


 public:

  PiTracker();
  ~PiTracker();

  int UsbConnect(int Vid,int Pid,int writeEp, int readEp);
  int Rs232Connect(const char* port,int baud=115200);
  int WriteTrkData(void* data,int len);
  int ReadTrkData(void* buf,int maxLen);
  int GetCnxType();
  void CloseTrk();

 private:

  int WriteUsbData(void* data,int len);
  int WriteRs232Data(void* data,int len);
  int ReadUsbData(void* buf,int len);
  int ReadRs232Data(void* buf,int maxLen);


  libusb_device_handle* m_handle;
  int m_cnxType;
  int m_usbWriteEp;
  int m_usbReadEp;
  int m_usbVid;
  int m_usbPid;
  int m_bCloseUsbLibrary;

  int m_FtContUsb;  // Fastrak needs some special flags 
  int m_isFt;       // It is a special case since it puts its USB continuous data
  int m_lastFtCont; // over an interrupt endpoint

  int m_rs232Port;
  struct termios m_initialAtt;

  pthread_mutex_t m_mutex;



};


#endif
