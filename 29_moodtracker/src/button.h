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
#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button
{
protected:
    int btnPin;
    int state;
    int result;
    unsigned long buttonclickedMS;
    unsigned long buttonDownMS;

public:
    Button(int pin);
    void start();
    int checkBTN();
    bool isPressed();
};

#endif
