/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 5: led water
*  
*  This lesson will show you how to use led water.
*  That's led1-led4 will on and off in turn.
*
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  led.on();                                        // led on
*  led.off();                                       // led off
*  led.state();                                     // return led state
*********************************************************************************************************/

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
    
    delay(SPEED);
    
    led2.on();
    led1.off();
    
    delay(SPEED);
    
    led3.on();
    led2.off();
    
    delay(SPEED);
    
    led4.on();
    led3.off();
    
    delay(SPEED);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/