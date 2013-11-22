// 

#include <Wire.h>
#include <TTSDisplay.h>


TTSDisplay disp;

void setup()
{
    
}

void loop()
{
    disp.num(1024);                         // display a number: 1024, you can input 0-9999
    delay(1000);                            // wait 1s
    
    disp.time(11, 26);                      // display time, 11:26
    disp.pointOn();                         // display :
    delay(1000);                            // wait 1s
}