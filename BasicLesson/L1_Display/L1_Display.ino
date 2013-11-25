/* 
  Tick Tock Shield Basic Lesson 1: display
  This lesson will show you how to use the 4 - 7-SEG Display
  
  you can use the following functon:
  
  disp.display(int loca, int num);          // control a  nixie tube
  disp.num(int num);                        // display a number
  disp.time(int hour, int min);             // display time
  disp.clear();                             // clear display
  disp.pointOn();                           // display :
  disp.pointOff();                          // clear :
*/

#include <Wire.h>
#include <TTSDisplay.h>


TTSDisplay disp;                            // instantiate an object

void setup()
{
    // nothing to setup
}

void loop()
{
    disp.num(1024);                         // display a number: 1024, you can input 0-9999
    delay(1000);                            // wait 1s
    
    disp.time(11, 26);                      // display time, 11:26
    disp.pointOn();                         // display :
    delay(1000);                            // wait 1s
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/