/* 
  Tick Tock Shield Basic Lesson 5: water
  This lesson will show you how to use led water.
  
  you can use the following functon:
  
  led.on();                                         // led on
  led.off();                                        // led off
  led.state();                                      // return led state
*/

#include <Wire.h>
#include <TTSLed.h>

#define SPEED   200                                 // water speed


TTSLed led1(TTSLED1);                               // instantiate an object of led 1
TTSLed led2(TTSLED2);                               // instantiate an object of led 2
TTSLed led3(TTSLED3);                               // instantiate an object of led 3
TTSLed led4(TTSLED4);                               // instantiate an object of led 4


void setup()
{
    // nothing to setup
}

void loop()
{

    led1.on();
    led4.off();
    
    delay(200);
    
    led2.on();
    led1.off();
    
    delay(200);
    
    led3.on();
    led2.off();
    
    delay(200);
    
    led4.on();
    led3.off();
    
    delay(200);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/