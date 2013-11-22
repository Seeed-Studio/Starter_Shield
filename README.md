## Tick Shield Library V2.0 ##




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

	TTSButton button(Pin);
	
	button.get();                                       // return button state, HIGH or LOW
	button.pressed();                                   // return HIGH when button is pressed
	button.released();                                  // return HIGH when button is released


### Display ###

	TTSDisplay disp();
	
	disp.ctrl(int loca, int num);                       // control a  nixie tube 
	disp.num(int num);                                  // display a number  
	disp.time(int hour, int min);                       // display time

### LED ###


	TTSLed led(Pin);
	
	led.on();                                           // led on
	led.off();                                          // led off
	led.state();                                        // return led state
