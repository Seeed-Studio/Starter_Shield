/*
  Tick Tock Shield Basic Lesson 6: Light Sensor
  This lesson will show you how to use Temperature Sensor
  
  you can use the following functon:
  
  temp.get()                                        // return value of temperature sensor
*/

#include <Wire.h>
#include <TTSDisplay.h>
#include <TTSTemp.h>
#include <TTSBuzzer.h>

TTSDisplay disp;                                    // instantiate an object of display
TTSTemp temp;                                       // instantiate an object of temperature
TTSBuzzer buz;                                      // instantiate an object of buzzer

void setup()
{
    // nothing to setup
}

void loop()
{

    int valTemp = temp.get();                       // get light sensor value
    
    disp.num(valTemp);                              // display light sensor value
    
    if(valTemp >= 30)
    {
        buz.on();
    }
    else
    {
        buz.off();
    }
    
    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/