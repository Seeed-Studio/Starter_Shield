#include "Wire.h"
#include <TimerOne.h>
#include <MsTimer2.h>
#include <EEPROM.h>
#include "TM1636.h"
#include "TickShield.h"

unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;
#define ON 1
#define OFF 0

// Global Variables
int command = 0;		 // This is the command char, in ascii form, sent from the serial port	   
int i;
long previousMillis = 0;		  // will store last time Temp was updated
//  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test; 

boolean flag_2s;
boolean flag_10s;
boolean flag_display_time = 1;
uint8_t counter_times = 20;
boolean flag_500ms_blink;
boolean flag_scan_again;
uint8_t counter_500ms;
/*status definitions for the tick shield control system*/
#define SYSTEM_NORAML    0 //It is the default status,and the system will turn to "normal" status 
//when the system is in "adjusting" status.
#define SYSTEM_ADJUSTING 1 //It will turn to "adjusting" status when the "menu" key is pressed 
//at the "normal" status. 
#define SYSTEM_ALARMING  2
uint8_t system_states;


TickShield tickshield;
extern int8_t disp[4];
extern byte g_hand;

void setup() 
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  tickshield.init();

  tickshield.displayTime();
  MsTimer2::set(500, Timer2ISR); // 500ms period
  MsTimer2::start();
	/*Run the 4 LEDs from left to right*/
  tickshield.runLED();
	/*Consider whether it is the first time to load the firmware*/
  if(isFirstLoad())
    tickshield.setAlarm(12,0);
  else tickshield.getAlarm();
  /*When system starts, adjust the brightness of the digital tube 
   		according to the ambient light intensity.*/
  uint8_t lightlevel; 
  lightlevel = tickshield.getLightLevel();
  tickshield.adjustBrightness(lightlevel);
  /*Read the ambient temperature and display on the digital tube.*/
  tickshield.displayTemperature(tickshield.getTemperature());
  delay(1000);
}
void loop() 
{
  while(1)systemStart();
}
//-----------------------------------
void systemStart()
{
  if(SYSTEM_NORAML == system_states)
  {

    if(Update)
    { 
      Update = 0;
      if(ClockPoint)
      {
        tm1636.point(POINT_ON);
      }
      else tm1636.point(POINT_OFF); 
      tickshield.getTime();
      if(tickshield.isAlarmEnable())
      {
        tm1636.point(POINT_ON);
        tickshield.displayTime();
        system_states = SYSTEM_ALARMING;
        return;
      }
      if(flag_display_time)tickshield.displayTime();

      if(flag_2s)
      {
        flag_2s = 0;
        flag_display_time = 1;

        counter_times = 20;
        halfsecond = 0;
      }
      if(flag_10s)
      {
        flag_10s = 0;
        flag_display_time = 0;
        tm1636.point(POINT_OFF);
        tickshield.displayTemperature(tickshield.getTemperature());
        counter_times = 4;
        halfsecond = 0;
      }
      if((flag_scan_again)&&(KEY_MENU == tickshield.scanKey()))
      {
        tickshield.writeToAdjustArea();
        tickshield.processKey();
        system_states = SYSTEM_ADJUSTING;
      }

    }
  }
  else if(SYSTEM_ADJUSTING == system_states)
  {
    tickshield.scanKey();
    tickshield.processKey();
    tickshield.processSystemStatus();
    if(tickshield.getQuitReq())
    {
      system_states = SYSTEM_NORAML;
      counter_500ms = 0;
      flag_scan_again = 0;
    }
    else flag_scan_again = 1;
  }
  else if(SYSTEM_ALARMING == system_states)
  {
    /*It will sound alarm for a minute untill the "MENU" key is pressed*/
    if(tickshield.isAlarmEnable())
    {
      tickshield.alarming();
    }
    else 
    {
      tickshield.turnOffAlarm();
      system_states = SYSTEM_NORAML;
    }
    if(KEY_MENU == tickshield.scanKey())
    {
      tickshield.turnOffAlarm();
      system_states = SYSTEM_NORAML;
    }
  }
}

//--------------------------------------
boolean isFirstLoad()
{
  unsigned char mark[] = "ALARM";
  unsigned char temp_data[5];
  for(unsigned char i = 0;i < 5;i ++)
  {
    temp_data[i] = EEPROM.read(i);
    if(temp_data[i] != mark[i])
    {
      EEPROM.write(0,mark[0]);
      EEPROM.write(1,mark[1]);
      EEPROM.write(2,mark[2]);
      EEPROM.write(3,mark[3]);
      EEPROM.write(4,mark[4]);
      return true;
    }
  }
  return false;
}

//--------------------------
void Timer2ISR()
{
  halfsecond ++;
  if(halfsecond  == counter_times)
  {
    halfsecond  = 0;
    if(counter_times == 4)flag_2s = 1;
    else if(counter_times == 20)flag_10s = 1;
  }
  Update = 1;
  ClockPoint = (~ClockPoint) & 0x01;
  flag_500ms_blink = ~flag_500ms_blink;
  if(tickshield.isAdjustingTime())
  {
    if(g_hand == HOUR)
    {
      if(flag_500ms_blink)
      {
        disp[0] = INDEX_BLANK;
        disp[1] = INDEX_BLANK;
      }
    }
    else
    {
      if(flag_500ms_blink)
      {
        disp[2] = INDEX_BLANK;
        disp[3] = INDEX_BLANK;
      }
    }
    tm1636.display(disp);
  }
  counter_500ms ++;
  if(counter_500ms == 6)
  {
    counter_500ms = 0;
    flag_scan_again = 1;
  }

}



