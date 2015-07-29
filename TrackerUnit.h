// PingPong.h


/*
Polhemus Tracker Terminal (PiTerm) version 1.0.3 -- Terminal Interface to Polhemus Trackers: Fastrak, Patriot, and Liberty
Copyright  ©  2009-2011  Polhemus, Inc.

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



#ifndef PINGPONG_H_
#define PINGPONG_H_

#define NUMBUFS   10

class TrackerUnit {

 private:

  BYTE* m_buf[NUMBUFS];
  int m_readInd;
  int m_writeInd;
  int m_size;
  int m_len[NUMBUFS];
  pthread_mutex_t m_mutex;

  void IncrInd(int& ind);

 public:

  TrackerUnit();
  ~TrackerUnit();

  int InitTrackerUnit(int);
  int GetBufferSize();
  int IsDataAvail();
  int ReadPP(BYTE*);
  int  WritePP(BYTE*,int);
  void ClearBuffers();
};





#endif
