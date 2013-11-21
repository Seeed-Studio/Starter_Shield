/*
  TTSTime.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-11-21
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __TTSTIME_H__
#define __TTSTIME_H__
#ifndef uchar
#define uchar unsigned char 
#endif


class TTSTime{

private:

    uchar decToBcd(uchar val);
    uchar bcdToDec(uchar val);
public:

    void setTime(uchar hour, uchar min, uchar sec);                 // set time
    void getTime(uchar *hour, uchar *min, uchar *sec);              // get time
    uchar getHour();                                                // get hour
    uchar getMin();                                                 // get minutes
    uchar getSec();                                                 // get second

};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/