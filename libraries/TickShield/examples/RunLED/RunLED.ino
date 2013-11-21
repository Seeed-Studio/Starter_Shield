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
  byte speed = 1;
  tickshield.runLED(speed++);//run fast
  tickshield.runLED(speed++);
  tickshield.runLED(speed++);//more slowly
}

