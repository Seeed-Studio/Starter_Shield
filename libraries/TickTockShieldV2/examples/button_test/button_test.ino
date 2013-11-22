// test button

#include <Wire.h>
#include <Streaming.h>

#include <TTSButton.h>
#include <TTSBuzzer.h>
#include <TTSLight.h>


TTSButton button1(TTSK1);
TTSButton button2(TTSK2);
TTSButton button3(TTSK3);

TTSBuzzer buz;

TTSLight light;


int state = 0;

void setup()
{
    Serial.begin(115200);
    cout << "hello world" << endl;
    
    cout << light.get() << endl;
    
    
    while(1)
    {
        cout << analogRead(A1) << endl;
        delay(100);
    }
}

void loop()
{
    if(button1.pressed())
    {
        delay(10);
        if(button1.pressed())
        {
            cout << "button1 pressed" << endl;
            
            state = 1-state;
            
            if(state)buz.on();
            else buz.off();
            
            cout << light.get() << endl;
        }
        
        while(button1.pressed());
        
    }
}