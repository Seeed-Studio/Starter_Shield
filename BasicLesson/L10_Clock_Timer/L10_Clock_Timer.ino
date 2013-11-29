/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 10: Clock
*
*  This lesson will show you how to use RTC and timer1
*  We will set time to RTC first, then get time from it and display in 7-SEG display.
*  Timer one will interrupt per 500ms to display time. 
*  
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  time.setTime(int hour, int min, int sec);        // set time
*  time.getTime(int *hour, int *min, int *sec);     // get time
*  time.getHour();                                  // return hour
*  time.getMinute();                                // return minutes
*  time.getSecond();                                // return seconds
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
#include <TTSTime.h>
#include <TimerOne.h>


TTSDisplay disp;                                    // instantiate an object of display
TTSTime time;

int hour = 0;                                       // get hour
int min  = 0;                                       // get minutes
    
/*********************************************************************************************************
 * Function Name: timerIsr
 * Description:  timer on interrupt service function to display time per 500ms
 * Parameters: None
 * Return: None
*********************************************************************************************************/
void timerIsr()
{

    static unsigned char state_colon = 0;
    
    state_colon = 1-state_colon;
    
    if(state_colon)
    {
        disp.pointOn();                             // : on
        
    }
    else
    {
        disp.pointOff();                            // : off
    }
    
    disp.time(hour, min);                           // display time

}


void setup()
{
    time.setTime(14, 14, 20);                       // set time to 14:14:20
    
    Timer1.initialize(500000);                      // timer1 500ms
    Timer1.attachInterrupt( timerIsr ); 
}

void loop()
{
    hour = time.getHour();                          // get hour
    min  = time.getMin();                           // get minutes

    delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/