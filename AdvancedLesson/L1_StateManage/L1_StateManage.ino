// clock

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
#define ST_TEMP             2               // display temperature
#define ST_SETALARM         3               // set time of alarm
#define ST_ALARMING         4               // alarming
#define ST_LIGHT            5               // display light
#define ST_SETIME           6               // set time 


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
		
		if(keyMode.pressed())
		{
			delay(10);
			if(keyMode.pressed())
			{
				Serial.println("goto ST_SETTIME");
				led1.on();
                state = ST_SETIME;
				
				while(!keyMode.released());
			}
		}
	
        break;
        
        //---------------------------------- ST_SETIME ------------------------------------------
        case ST_SETIME:
        
		// if keyMode press, goto ST_SETALARM
		
		
		if(keyMode.pressed())
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
		}
		
        break;
        
        //---------------------------------- ST_SETALARM ----------------------------------------
        case ST_SETALARM:

		// if keyMode press, set ok, goto ST_TIME
		
		if(keyMode.pressed())
		{
			delay(10);
			if(keyMode.pressed())
			{
				Serial.println("set ok, goto ST_TIME");
				led2.off();
                
                state = ST_TIME;
				while(!keyMode.released());
			}
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