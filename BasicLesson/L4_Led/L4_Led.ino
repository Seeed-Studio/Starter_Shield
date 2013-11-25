/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 4: led
*
*  This lesson will show you how to use led.
*  We use button 1, 2, 3 to control led1, led2 and led4. 
*  When a button pressed, a led will on.
*
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  button.get();                                    // return button state, HIGH or LOW
*  button.pressed();                                // return HIGH when button is pressed
*  button.released();                               // return HIGH when button is released
*  
*  led.on();                                        // led on
*  led.off();                                       // led off
*  led.state();                                     // return led state
*********************************************************************************************************/

#include <Wire.h>
#include <TTSButton.h>
#include <TTSLed.h>


TTSButton but1(TTSK1);                              // instantiate an object of button 1
TTSButton but2(TTSK2);                              // instantiate an object of button 2
TTSButton but3(TTSK3);                              // instantiate an object of button 3

TTSLed led1(TTSLED1);                               // instantiate an object of led 1
TTSLed led2(TTSLED2);                               // instantiate an object of led 2
TTSLed led3(TTSLED3);                               // instantiate an object of led 3


void setup()
{
    // nothing to setup
}

void loop()
{
    if(but1.pressed())                              // if button1 pressed, then led1 on, or led1 off
    {
        led1.on();
    }
    else 
    {
        led1.off();
    }
    
    if(but2.pressed())                              // if button2 pressed, then led2 on, or led2 off
    {
        led2.on();
    }
    else
    {
        led2.off();
    }
    
    if(but3.pressed())                              // if button3 pressed, then led3 on, or led3 off
    {
        led3.on();
    }
    else
    {
        led3.off();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/