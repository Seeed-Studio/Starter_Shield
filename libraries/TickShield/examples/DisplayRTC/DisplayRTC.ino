#include "Wire.h"
#include <TimerOne.h>
#include <MsTimer2.h>
#include <EEPROM.h>
#include "TM1636.h"
#include "TickShield.h"

unsigned char ClockPoint = 1;
unsigned char Update;

#define ON 1
#define OFF 0

TickShield tickshield;


void setup() 
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  tickshield.init();

  MsTimer2::set(500, Timer2ISR); // 500ms period
  MsTimer2::start();
}
void loop() 
{
  while(1)systemStart();
}
//-----------------------------------
void systemStart()
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
      tickshield.displayTime();
    }
}

//--------------------------
void Timer2ISR()
{
  Update = 1;
  ClockPoint = (~ClockPoint) & 0x01;
}



