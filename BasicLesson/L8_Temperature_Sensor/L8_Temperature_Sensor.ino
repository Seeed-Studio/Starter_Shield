/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 8: Temperature Sensor
*
*  This lesson will show you how to use Temperature Sensor
*  And display the value in 7-SEG display
*
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  temp.get()                                       // return value of temperature sensor
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
#include <TTSTemp.h>


TTSDisplay disp;                                    // instantiate an object of display
TTSTemp temp;                                       // instantiate an object of temperature


void setup()
{
    // nothing to setup
}

void loop()
{
    int valTemp = temp.get();                       // get light sensor value
    
    disp.num(valTemp);                              // display light sensor value
    
    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/