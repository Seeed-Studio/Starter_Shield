// 

#include <Wire.h>
#include <TTSDisplay.h>


TTSDisplay disp;

void setup()
{
    
}

void loop()
{
    static int i=0;
    
    disp.num(i++);
    
    
    if(i > 1023)i=0;
    delay(1);
}