#include "Wire.h"
#include <TimerOne.h>
#include <EEPROM.h>
#include "TM1636.h"
#include "TickShield.h"
/*Declare a TickShield Class object*/
TickShield tickshield;

void setup()
{
  tickshield.init();
}
void loop()
{
	int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  int8_t ListDisp[4];
  unsigned char i = 0;
  unsigned char count = 0;
  delay(150);
  while(1)
  {
    i = count;
    count ++;
    if(count == sizeof(NumTab)) count = 0;
    for(unsigned char BitSelect = 0;BitSelect < 4;BitSelect ++)
    {
      ListDisp[BitSelect] = NumTab[i];
      i ++;
      if(i == sizeof(NumTab)) i = 0;
    }
    tickshield.display(ListDisp);
    delay(300);
  }
}

