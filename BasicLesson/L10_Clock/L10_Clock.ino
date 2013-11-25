/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 10: Clock
*
*  This lesson will show you how to use RTC.
*  We will set time to RTC first, then get time from it and display in 7-SEG display
*  
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  time.setTime(int hour, int min, int sec);        // set time
*  time.getTime(int *hour, int *min, int *sec);     // get time
*  time.getHour();                                  // return hour
*  time.getMinute();                                // return minutes
*  time.getSecond();                                // return seconds
*  
*  disp.display(int loca, int num);                 // control a  nixie tube
*  disp.num(int num);                               // display a number
*  disp.time(int hour, int min);                    // display time
*  disp.clear();                                    // clear display
*  disp.pointOn();                                  // display :
*  disp.pointOff();                                 // clear :
*********************************************************************************************************/

#include <Wire.h>
#include <TTSDisplay.h>
#include <TTSTime.h>


TTSDisplay disp;                                    // instantiate an object of display
TTSTime time;


void setup()
{
    time.setTime(14, 14, 20);                       // set time to 14:14:20
}

void loop()
{
    int hour = time.getHour();                      // get hour
    int min  = time.getMin();                       // get minutes

    disp.time(hour, min);                           // display hour:min
    
    disp.pointOn();                                 // : on
    delay(500);                                     
    disp.pointOff();                                // : off
    delay(500);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/