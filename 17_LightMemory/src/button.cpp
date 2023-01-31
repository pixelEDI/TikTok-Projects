#include "button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    btnPin = pin;
    pinMode(btnPin, INPUT);
    state = LOW;
}

bool Button::isPressed()
{
   bool result=false;

    int prevState = state;
    state = digitalRead(btnPin);

    if(prevState == LOW && state == HIGH){
        buttonclickedMS=millis();
        result=false;
    }
    else if( prevState == HIGH && state == LOW){
        //here comes the logic 
     
        if(millis()- buttonclickedMS < 50){
            //debounce area - nothing to do
            result=false;
        }
        else if(millis() - buttonclickedMS > 50) {
            //Serial.println("short click");
            result=true;
        }
        
    }

    return result;
}
