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
	/*The darker the ambient light intensity, the darker the LED*/
  uint8_t light_level;
	light_level = tickshield.getLightLevel();
  analogWrite(LED_BRIGHT_ADJUST,light_level*30);
}

