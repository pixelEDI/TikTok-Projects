/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://linktr.ee/pixeledi
Moodtracker | V1.0 | 10.2023
*/
#include "button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    btnPin = pin;
    state = LOW;
    pinMode(btnPin, INPUT_PULLUP);
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
        else if (millis() - buttonclickedMS > 50)
        {
            // Serial.println("short click");
            result = 1;
        }
        // else if (millis() - buttonclickedMS > 2000)
        // {
        //     // Serial.println("long long click");
        //     result = 2;
        // }
    }

    return result;
}
