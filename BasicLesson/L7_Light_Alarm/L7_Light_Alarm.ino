/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 7: Light Alarm

*  This lesson will show you how to use Light Sensor
*  When value of light less than 100, the buzzer will on. 
*  
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  light.get();                                     // return light sensor data, 0-1023
*
*  buzzer.on();                                     // on
*  buzzer.off();                                    // off
*  buzzer.state();                                  // return state of buzzer, HIGH:on, LOW:off
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