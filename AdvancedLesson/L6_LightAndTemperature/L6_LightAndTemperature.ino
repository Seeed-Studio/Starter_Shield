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

int alarm_hour = 8;                         // hour of alarm
int alarm_min  = 0;                         // minutes of alarm

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

/*********************************************************************************************************
 * Function Name: isAlarm
 * Description:  detect if alarm, if get alarm, buzzer on.
 * Parameters: None
 * Return: 1: alarm
           0: nothing
*********************************************************************************************************/
unsigned char isAlarm()
{
    if(now_hour == alarm_hour && now_min == alarm_min && now_sec == 1)
    {
        state = ST_ALARMING;
        cout << "goto alarm" << endl;
        buz.on();
        return 1;
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
        
        isAlarm();                                              // check if alarm
        
        if(keyDown.pressed())                                   // press keyDown, display temperature
        {
            led3.on();                                          // led 3 on for 10ms
            delay(10);
            led3.off();
            while(keyDown.pressed())                            // display temperature until release keyDown
            {
                state = ST_TEMP;
                int temperature = temp.get();
                disp.num(temperature);
            }
            state = ST_TIME;  
        }
        
        if(keyUp.pressed())                                     // press keyUp, display light sensor value
        {

            led4.on();                                          // led4 on for 10ms
            delay(10);
            led4.off();
            while(keyUp.pressed())                              // display light value until release keyUp
            {
                state = ST_LIGHT;
                int val_light = light.get();
                disp.num(val_light);
                
                delay(100);
            }
            state = ST_TIME;  
        }
        
        break;
        
        //---------------------------------- ST_SETIME ------------------------------------------
        case ST_SETIME:

        // if press keyMode, goto set alarm time mode
        if(keyEvent(keyMode, ST_SETALARM, "set time ok!\r\n goto ST_SETALARM"))     
        {
            time.setTime(now_hour, now_min, 0);                 // display alarm time
            disp.time(alarm_hour, alarm_min);
            
            led1.off();                                         // led2 on, led1 off to indicate set alarm
            led2.on();
        }
        
        if(keyEvent(keyUp, 0, "time hour ++"))                  // press keyUp, hour +1
        {
            now_hour++;
            if(now_hour>23)now_hour = 0;                        // change to 0 while exceed 23
            
            disp.time(now_hour, now_min);
        }
        
        if(keyEvent(keyDown, 0, "time minutes ++"))             // press keyDown, minutes +1
        {
            now_min++;
            if(now_min>59)now_min = 0;                          // change to 0 while exeed 59
            
            disp.time(now_hour, now_min);
        }
        
		
        break;
        
        //---------------------------------- ST_SETALARM ----------------------------------------
        case ST_SETALARM:

        // press keyMode to finish setting. then goto display time mdoe
        if(keyEvent(keyMode, ST_TIME, "set alarm ok!\r\ngoto ST_TIME"))
        {
            led2.off();
        }
        
        if(keyEvent(keyUp, 0, "alarm hour ++"))                 // press keyUp, alarm hour +1
        {
            alarm_hour++;
            if(alarm_hour>23)alarm_hour = 0;          
            disp.time(alarm_hour, alarm_min);
        }
        
        if(keyEvent(keyDown, 0, "alarm minutes ++"))            // press keyDown, alarm minutes +1
        {
            alarm_min++;
            if(alarm_min>59)alarm_min = 0;
            disp.time(alarm_hour, alarm_min);
        }
        
        
        break;
        
        //---------------------------------- ST_ALARMING ----------------------------------------
        case ST_ALARMING:

        if(light.get() < 150)                                   // if light sensor value less than 150
        {
            buz.off();
            state = ST_TIME;
        }
        break;
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/