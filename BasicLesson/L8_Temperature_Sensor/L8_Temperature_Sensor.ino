/*
  Tick Tock Shield Basic Lesson 6: Light Sensor
  This lesson will show you how to use Temperature Sensor
  
  you can use the following functon:
  
  temp.get()                                        // return value of temperature sensor
*/

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