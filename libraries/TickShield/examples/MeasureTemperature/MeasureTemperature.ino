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
	 /*Read the ambient temperature and display on the digital tube.*/
	int8_t temperature;
	temperature = tickshield.getTemperature();
	tickshield.displayTemperature(temperature);
	delay(500);
}

