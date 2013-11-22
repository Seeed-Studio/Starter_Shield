//  Demo function:Use the three buttons to control four LEDs.
//			Note: K3-menu, K2-increase,K1-decrease
//			Power up: all the LED off
//	Every time the menu key pressed, the status changes from TEST_START
//	to TEST_END or from TEST_END to TEST_START.
//  When it starts, "increase" key can turn on one more LED from right to left
//	every time the "increase" key pressed. 
//	The "decrease" key operation is inverse process of "increase" key's.
//
//  Author:Frankie.Chu
//  Date:23 September, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include <TimerOne.h>

/*If do not want to print any message on the serial monitor, 
you can comment out the following line of code like "//#define DEBUG 1"*/
#define DEBUG 1

//-------pin definition of LEDs---------------//
#define LED_CLOCK_ADJUST	5
#define LED_ALARM_ADJUST	4
#define LED_ALARM_ENABLE	3
#define LED_BRIGHT_ADJUST	2
//-------pin definition of keys---------------//
#define KEY_MENU	11
#define KEY_UP		10
#define KEY_DOWN	9

uint8_t status;//the status of the test
	#define TEST_END   0
	#define TEST_START 1
	#define TESTING	   2
	
const int LEDS_PIN[] = 
{
	LED_BRIGHT_ADJUST,
	LED_ALARM_ENABLE,
	LED_ALARM_ADJUST,
	LED_CLOCK_ADJUST
};
int8_t LED_on_number = -1;//tell which LED is on that is nearest to the off LED
boolean flag_test_start;
boolean flag_all_on;

void setup()
{
#ifdef DEBUG
	Serial.begin(9600);
#endif
	/*Initialization for the hardware,and should be call first*/
	init_pins();
	Timer1.initialize(500000); // set a timer of length 500000 microseconds 
	Timer1.attachInterrupt( timer1Isr ); // attach the service routine here
}
void loop()
{
	int16_t key_pressed = scanKey();
	if(KEY_MENU == key_pressed)
	{
	/*Every time the menu key pressed, the status changes from TEST_START */
	/*to TEST_END or from TEST_END to TEST_START.						  */
		flag_test_start = ~flag_test_start;
		if(flag_test_start)status = TEST_START;
		else status = TEST_END;
	}
	else if(KEY_UP == key_pressed)
	{
	/*When it starts, "UP" key can turn on one more LED from right to left*/
	/*every time the "UP" key pressed. */
		if(status == TEST_START)status = TESTING;
		if(status == TESTING)turnOnMoreLED();
	}
	else if(KEY_DOWN == key_pressed)
	{
	/*When it starts, "DOWN" key can turn off one more LED from left to right*/
	/*every time the "DOWN" key pressed. */
		if(status == TEST_START)status = TESTING;
		if(status == TESTING)turnOffMoreLED();
	}
	/*if a key has been pressed, wait for extra 200ms*/
	if(key_pressed > 0)delay(200);
}
/*Initialization for the hardware,and should be call first*/
void init_pins()
{
	/*All keys are set to be input pins*/
	pinMode(KEY_MENU, INPUT);
	digitalWrite(KEY_MENU, HIGH);
	pinMode(KEY_UP, INPUT);
	digitalWrite(KEY_UP, HIGH);
	pinMode(KEY_DOWN, INPUT);
	digitalWrite(KEY_DOWN, HIGH);
	pinMode(LED_CLOCK_ADJUST, OUTPUT);
	pinMode(LED_ALARM_ADJUST, OUTPUT);
	pinMode(LED_BRIGHT_ADJUST, OUTPUT);
	pinMode(LED_ALARM_ENABLE, OUTPUT);
	turnOffAll();//Turn off all the LEDs first.
}
/*Turn on one LED*/
inline void turnOn(int pinLED)
{
	digitalWrite(pinLED, HIGH);
}
/*Turn Off one LED*/
inline void turnOff(int pinLED)
{
	digitalWrite(pinLED, LOW);
}
/*Turn on all the LEDs*/
inline void turnOnAll()
{
	turnOn(LED_CLOCK_ADJUST);
	turnOn(LED_ALARM_ADJUST);
	turnOn(LED_BRIGHT_ADJUST);
	turnOn(LED_ALARM_ENABLE);
}
/*Turn off all the LEDs*/
inline void turnOffAll()
{
	turnOff(LED_CLOCK_ADJUST);
	turnOff(LED_ALARM_ADJUST);
	turnOff(LED_BRIGHT_ADJUST);
	turnOff(LED_ALARM_ENABLE);
}

/*Turn on one more LED*/
void turnOnMoreLED()
{
	if(LED_on_number < 3)
	{
		LED_on_number ++;
		turnOn(LEDS_PIN[LED_on_number]);
		for(byte i = LED_on_number + 1;i < 4;i ++)
			turnOff(LEDS_PIN[i]);
	}
}

/*Turn off one more LED*/
void turnOffMoreLED()
{
	if((LED_on_number > 0) || (LED_on_number == 0))
	{
		turnOff(LEDS_PIN[LED_on_number]);
		LED_on_number --;
	}
}

/*Scan keys and get to know which one is pressed*/
int16_t scanKey()
{
	int16_t pin_number = -1;
	if(digitalRead(KEY_MENU) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_MENU) == LOW)
		{
			pin_number = KEY_MENU;
		}
	#ifdef DEBUG
		Serial.println("KEY_MENU is pressed");
	#endif
		
	}
	else if(digitalRead(KEY_UP) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_UP) == LOW)
		{
			pin_number = KEY_UP;
		}
	#ifdef DEBUG
		Serial.println("KEY_UP is pressed");
	#endif
	}
	else if(digitalRead(KEY_DOWN) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_DOWN) == LOW)
		{
			pin_number = KEY_DOWN;
		}
	#ifdef DEBUG
		Serial.println("KEY_DOWN is pressed");
	#endif
	}
	return pin_number;
}
/*Timer one interrupt service routine*/
/*Function:if it start, all the LEDs will blink every second.*/
void timer1Isr()
{
	if(status == TEST_START)
	{
		flag_all_on = ~flag_all_on;
		if(flag_all_on)
		{
			LED_on_number = 3;
			turnOnAll();
		}
		else 
		{
			LED_on_number = -1;
			turnOffAll();
		}
	}
	else if(status == TEST_END) 
	{
		turnOffAll();
		LED_on_number = -1;
	}
}
