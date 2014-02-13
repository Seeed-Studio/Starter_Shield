## Tick Tock Shield Library V2.0 ##

Tick Tock Shield is a perfect start for beginners of Arduino world. You can learn and practice basic soldering tricks and programming principles when tinkering with this kit. Electronic could be fun even if you have bare technical knowledge cause we get your back by preparing a detailed soldering guide and a fully supported library of programming examples from easy to difficult. Hope you have fun and gain some knowledge with this kit!

Tick Tock Shield contains most common resources for a basic electronic project, like buttons, sensors, buzzer and display. After you're done with the soldering task, it turns out to be a geek style alarm clock which can auto adjust the brightness of display and keep in synch with real world time.


[![WiFiBeeV2](http://www.seeedstudio.com/depot/images/product/tickshield.jpg)](http://www.seeedstudio.com/depot/tick-tock-shield-p-1371.html?cPath=84_13)





<br>
## Usage ##

This is a Sketchbook of Arduino.([How to use Sketchbook](http://www.seeedstudio.com/wiki/How_To_Use_Sketchbook "How to use Sketchbook"))

This Sketchbook includes a set of Basic Demo and a Advanced Demo.

The Basic Demo include:


1. Display
2. Button and Counter
3. Button and Counter with Key Debounce
4. Button and LED
5. Run Hourse LED
6. Light Sensor
7. Light Sensor and Buzzer
8. Display Temperature
9. Temperature and Buzzer
10. Set and display Time




<br>
## Class and Function
Tick Tcok Shield include RTC, Buzzer, Light Sensor, Temperature Sensor, 3 Buttons, Display as well as 4 LEDs. Each of those has a class, whick make it very to use. 

### RTC ###

	TTSTime time;                                       // TTS: Tick Tock Shield
	
	time.setTime(int hour, int min, int sec);           // set time
	time.getTime(int *hour, int *min, int *sec);
	time.getHour();                                     // return hour
	time.getMinute();                                   // return minutes
	time.getSecond();									// return seconds

    
### Buzzer ###

	TTSBuzzer buzzer;
	
	buzzer.on();                                        // on
	buzzer.off();                                       // off
	buzzer.state();                                     // return state of buzzer, HIGH:on, LOW:off


### LightSensor ###

	TTSLight light;
	
	light.get();                                        // return light sensor data, 0-1023


### Temperature Sensor ###

	TTSTemperature temp;
	
	temp get();                                         // return temperature value, int


### Button ###

	TTSButton button(Pin);								// TTSK1, TTSK2, TTSK3
	
	button.get();                                       // return button state, HIGH or LOW
	button.pressed();                                   // return HIGH when button is pressed
	button.released();                                  // return HIGH when button is released


### Display ###

	TTSDisplay disp();
	
	disp.display(int loca, int num);                   	// control a  nixie tube 
	disp.num(int num);                                  // display a number  
	disp.time(int hour, int min);                       // display time
	disp.clear();										// clear display
	disp.pointOn();										// display :
	disp.pointOff();									// clear :

### LED ###

	TTSLed led(Pin);									// TTSLED1, TTSLED2, TTSLED3, TTSLED4
	
	led.on();                                           // led on
	led.off();                                          // led off
	led.state();                                        // return led state


For more information, please refer to [wiki page](http://www.seeedstudio.com/wiki/Tick_Tock_Shield_Kit "wiki page")

----

This software is written by luweicong@seeedstudio.com for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>




[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/Tick_Tock_Shield_V2)](https://github.com/igrigorik/ga-beacon)
