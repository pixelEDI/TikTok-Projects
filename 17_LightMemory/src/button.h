#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button
{
private:
    int btnPin;
    int state;
    unsigned long buttonclickedMS;

public:
    Button(int pin);
    bool isPressed();
};

#endif