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


int now_hour;                               // hour of running
int now_min;                                // minutes of running
int now_sec;                                // second of running


/*********************************************************************************************************
 * Function Name: timerIsr
 * Description:  timer on interrupt service function to display time per 500ms
 * Parameters: None
 * Return: None
*********************************************************************************************************/
void timerIsr()
{
    static unsigned char state_colon = 0;
    if(ST_TIME == state || ST_ALARMING == state)
    {   
        state_colon = 1-state_colon;
        if(state_colon)
        {
            disp.pointOn();                             // : on
        }
        else
        {
            disp.pointOff();                            // : off
        }
        disp.time(now_hour, now_min); 
    }
}

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
    
    
    now_hour = time.getHour();
    now_min  = time.getMin();
    
    Timer1.initialize(500000);                                  // timer1 500ms
    Timer1.attachInterrupt( timerIsr ); 
}

void loop()
{

    switch(state)
    {
    
        //---------------------------------- ST_TIME --------------------------------------------
        case ST_TIME:

        if(keyEvent(keyMode, ST_SETIME, "goto ST_SETIME"))
        {
            led1.on();
        }
        
        // get time
        now_hour = time.getHour();
        now_min  = time.getMin();
        now_sec  = time.getSec();
        
        
	
        break;
        
        //---------------------------------- ST_SETIME ------------------------------------------
        case ST_SETIME:

        if(keyEvent(keyMode, ST_SETALARM, "goto ST_SETALARM"))
        {
            led1.off();
            led2.on();
        }
        
		
        break;
        
        //---------------------------------- ST_SETALARM ----------------------------------------
        case ST_SETALARM:

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