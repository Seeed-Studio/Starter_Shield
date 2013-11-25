/* 
  Tick Tock Shield Basic Lesson 6: Light Sensor
  This lesson will show you how to use Light Sensor
  When value of light exceed 700, the buzzer will on. 
  
  you can use the following functon:
  
  buzzer.on();                                        // on
  buzzer.off();                                       // off
  buzzer.state();                                     // return state of buzzer, HIGH:on, LOW:off
*/

#include <Wire.h>
#include <TTSDisplay.h>
#include <TTSLight.h>
#include <TTSBuzzer.h>

TTSDisplay disp;                                    // instantiate an object of display
TTSLight light;                                     // instantiate an object of light sensor
TTSBuzzer buz;                                      // instantiate an object of buzzer

void setup()
{
    // nothing to setup
}

void loop()
{

    int valLight = light.get();                     // get light sensor value
    
    disp.num(valLight);                             // display light sensor value
    
    if(valLight < 100)                              // light value less than 100
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