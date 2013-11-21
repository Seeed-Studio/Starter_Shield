/*
  TTSTime.cpp
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

#include <Wire.h>
#include "TTSTime.h"

#define YEAR    13
#define MONTH   11
#define DAY     21
#define WEEK    4

#define DS1307_I2C_ADDRESS      0x68

/*********************************************************************************************************
 * Function Name: decToBcd
 * Description:  dec to bcd
 * Parameters: val - data input
 * Return: return bcd of val
*********************************************************************************************************/
uchar TTSTime::decToBcd(uchar val)
{
    return ( (val/10*16) + (val%10) );
}

/*********************************************************************************************************
 * Function Name: bcdToDec
 * Description:  bcd to dec
 * Parameters: val - data input
 * Return: return dec of val
*********************************************************************************************************/
uchar TTSTime::bcdToDec(uchar val)
{
    return ( (val/16*10) + (val%16) );
}

/*********************************************************************************************************
 * Function Name: setTime
 * Description:  set rtc time
 * Parameters: hour - hour, min - minutes, sec - second
 * Return: None
*********************************************************************************************************/
void TTSTime::setTime(uchar hour, uchar min, uchar sec)
{

    if(hour > 24 || hour < 0)return;
    if(min > 59 || min < 0)return;
    if(sec > 59 || min < 0)return;
    
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uchar)0x00);
    Wire.write(decToBcd(sec));                              // 0 to bit 7 starts the clock
    Wire.write(decToBcd(min));
    Wire.write(decToBcd(hour));                             // If you want 12 hour am/pm you need to set
                                                            // bit 6 (also need to change readDateDs1307)
    Wire.write(decToBcd(WEEK));
    Wire.write(decToBcd(DAY));
    Wire.write(decToBcd(MONTH));
    Wire.write(decToBcd(YEAR));
    Wire.endTransmission();
}

/*********************************************************************************************************
 * Function Name: getTime
 * Description:  get time
 * Parameters: *hour - hour, *min - minutes, *sec - second
 * Return: None
*********************************************************************************************************/
void TTSTime::getTime(uchar *hour, uchar *min, uchar *sec)
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uchar)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    
    uchar tmp = 0;
    
    *sec  = bcdToDec(Wire.read() & 0x7f);
    *min  = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);                   // Need to change this if 12 hour am/pm
    tmp   = bcdToDec(Wire.read());
    tmp   = bcdToDec(Wire.read());
    tmp   = bcdToDec(Wire.read());
    tmp   = bcdToDec(Wire.read());
}

/*********************************************************************************************************
 * Function Name: getHour
 * Description:  get hour
 * Parameters: None
 * Return: hour
*********************************************************************************************************/
uchar TTSTime::getHour()
{
    uchar hour, min, sec;
    getTime(&hour, &min, &sec);
    return hour;
}

/*********************************************************************************************************
 * Function Name: getMin
 * Description:  get minutes
 * Parameters: None
 * Return: minutes
*********************************************************************************************************/
uchar TTSTime::getMin()
{
    uchar hour, min, sec;
    getTime(&hour, &min, &sec);
    return min;
}

/*********************************************************************************************************
 * Function Name: getSec
 * Description:  get second
 * Parameters: None
 * Return: second
*********************************************************************************************************/
uchar TTSTime::getSec()
{
    uchar hour, min, sec;
    getTime(&hour, &min, &sec);
    return sec;
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/