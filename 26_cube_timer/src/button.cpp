#include "button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    btnPin = pin;
    pinMode(btnPin, INPUT_PULLUP);
    state = LOW;
}

void Button::start()
{
}


int Button::checkBTN()
{

    // return 0 = nothing to do
    // return 1 = short klick
    // return 2 = long klick
    result = 0;

    int prevState = state;
    state = digitalRead(btnPin);

    if (prevState == LOW && state == HIGH)
    {
        buttonclickedMS = millis();
        result = 0;
    }
    else if (prevState == HIGH && state == LOW)
    {
        // here comes the logic

        if (millis() - buttonclickedMS < 50)
        {
            // debounce area - nothing to do
            result = 0;
        }
        else if (millis() - buttonclickedMS > 50 && millis() - buttonclickedMS < 1500)
        {
            // Serial.println("short click");
            result = 1;
        }
        else if (millis() - buttonclickedMS > 2000)
        {
            // Serial.println("long long click");
            result = 2;
        }
    }

    return result;
}