// test button

#include <Streaming.h>
#include <TTSButton.h>
#include <Wire.h>

TTSButton button1(TTSK1);
TTSButton button2(TTSK2);
TTSButton button3(TTSK3);

void setup()
{
    Serial.begin(115200);
    cout << "hello world" << endl;
}

void loop()
{
    if(button1.pressed())
    {
        delay(10);
        if(button1.pressed())
        {
            cout << "button1 pressed" << endl;
        }
        
        while(button1.pressed());
        
    }
}