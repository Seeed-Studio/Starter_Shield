/* 
  Tick Tock Shield Basic Lesson 6: Light Sensor
  This lesson will show you how to use Light Sensor
  
  you can use the following functon:
  
  light.get();                                      // return light sensor data, 0-1023
*/

#include <Wire.h>
#include <TTSDisplay.h>
#include <TTSLight.h>

TTSDisplay disp;                                    // instantiate an object of display
TTSLight light;                                     // instantiate an object of light sensor


void setup()
{
    // nothing to setup
}

void loop()
{

    int valLight = light.get();                     // get light sensor value
    
    disp.num(valLight);                             // display light sensor value
    
    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/