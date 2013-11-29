/*********************************************************************************************************
*  Tick Tock Shield Advanced Lesson 2: StateManage
*  
*  This lesson will write a button check function which is useful and will be used in the sate machine.
*   
*  the function is : unsigned char keyEvent(TTSButton but, const unsigned char chg_state, const char *str_debug);
*  you can refer to the code, actually it's easy to understand.   
*
*  Then, you can find that, we'll use this function to replace such code:
*
*   if(keyMode.pressed())
*   {
*  	    delay(10);
*  	    if(keyMode.pressed())
*  	    {
*  		    Serial.println("goto ST_SETTIME");
*  		    led1.on();
*           state = ST_SETIME;
*  			
*  			while(!keyMode.released());
*       }
*   }
*
*  Author: Loovee
*  2013-11-29
*********************************************************************************************************/
#include <Wire.h>
#include <TimerOne.h>
#include <Streaming.h>

#include <TTSDisplay.h>
#include <TTSBuzzer.h>
#include <TTSLed.h>
#include <TTSButton.h>
#include <TTSLight.h>
#include <TTSTemp.h>
#include <TTSTime.h>


// STATE define here
#define ST_TIME             1               // normal mode, display time and temperature
#define ST_SETIME           2               // set time 
#define ST_SETALARM         3               // set time of alarm
#define ST_ALARMING         4               // alarming
#define ST_LIGHT            5               // display light
#define ST_TEMP             6               // display temperature


// object define here
TTSDisplay disp;                            // instantiate an object of display

TTSLed led1(TTSLED1);                       // instantiate an object of led1
TTSLed led2(TTSLED2);                       // instantiate an object of led2
TTSLed led3(TTSLED3);                       // instantiate an object of led3
TTSLed led4(TTSLED4);                       // instantiate an object of led4

TTSBuzzer buz;                              // instantiate an object of buzzer

TTSButton keyDown(TTSK1);                   // instantiate an object of button1
TTSButton keyUp(TTSK2);                     // instantiate an object of button2
TTSButton keyMode(TTSK3);                   // instantiate an object of button3

TTSLight light;                             // instantiate an object of light sensor

TTSTemp temp;                               // instantiate an object of temperature sensor

TTSTime time;                               // instantiate an object of rtc

int state = ST_TIME;                        // state

/*********************************************************************************************************
 * Function Name: keyEvent
 * Description:  detect key event
 * Parameters: but: which button
               chg_state: if get pressed, change to chg_state, if chg_state = 0, state remains.
               *str_debug: if get pressed, print str_debug
 * Return: 1: get pressed
           0: get nothing
*********************************************************************************************************/
unsigned char keyEvent(TTSButton but, const unsigned char chg_state, const char *str_debug)
{
    if(but.pressed())
    {
        delay(10);
        if(but.pressed())
        {
            cout << str_debug << endl;
            while(!but.released());
            state = chg_state ? chg_state : state;
            return 1;
        }
    }
    
    return 0;
}


void setup()
{
    Serial.begin(115200);
	Serial.println("hello world, let's start to make a clock!");
}

void loop()
{

    switch(state)
    {
    
        //---------------------------------- ST_TIME --------------------------------------------
        case ST_TIME:

		// if keyMode press, goto ST_SETIME
		// if alarming, goto ST_ALARMING
		
		/*if(keyMode.pressed())
		{
			delay(10);
			if(keyMode.pressed())
			{
				Serial.println("goto ST_SETTIME");
				led1.on();
                state = ST_SETIME;
				
				while(!keyMode.released());
			}
		}*/
        
        // the above code can change to:
        
        if(keyEvent(keyMode, ST_SETIME, "goto ST_SETIME"))
        {
            led1.on();
        }
        
        
	
        break;
        
        //---------------------------------- ST_SETIME ------------------------------------------
        case ST_SETIME:
        
		// if keyMode press, goto ST_SETALARM
		
		
		/*if(keyMode.pressed())
		{
			delay(10);
			if(keyMode.pressed())
			{
				Serial.println("goto ST_SETALARM");
				led1.off();
				led2.on();
                
                state = ST_SETALARM;
				while(!keyMode.released());
			}
		}*/
        
        // the above code can change to:
        
        if(keyEvent(keyMode, ST_SETALARM, "goto ST_SETALARM"))
        {
            led1.off();
            led2.on();
        }
        
		
        break;
        
        //---------------------------------- ST_SETALARM ----------------------------------------
        case ST_SETALARM:

		// if keyMode press, set ok, goto ST_TIME
		
		/*if(keyMode.pressed())
		{
			delay(10);
			if(keyMode.pressed())
			{
				Serial.println("set ok, goto ST_TIME");
				led2.off();
                
                state = ST_TIME;
				while(!keyMode.released());
			}
		}*/
        
        // the above code can change to:
        if(keyEvent(keyMode, ST_TIME, "goto ST_TIME"))
        {
            led2.off();
        }
        
        
        break;
        
        //---------------------------------- ST_ALARMING ----------------------------------------
        case ST_ALARMING:

        break;
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/