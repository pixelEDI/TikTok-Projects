/*


        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | twitter.com/pixeledi
Flamesensor| V1.0 | 09.2022
*/

#include <Arduino.h>

const byte ledGreen = 10;
const byte ledYellow = 9;
const byte ledRed = 8;
const byte cooler = 12;

unsigned long previousTime = 0;
unsigned long blinkDelay = 250;
byte redState = LOW;

void setup()
{
  Serial.begin(115200);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(cooler, OUTPUT);
}

void loop()
{
  int flameCheck = analogRead(A5);
  flameCheck = map(flameCheck, 0, 1023, 0, 3);
  unsigned long timenow = millis();

  switch (flameCheck)
  {
  case 0:
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(cooler, LOW);
    break;

  case 1:
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(cooler, LOW);
    break;

  case 2:
    digitalWrite(cooler, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);

    if (timenow - previousTime > blinkDelay)
    {
      previousTime = timenow;
      digitalWrite(ledRed, !digitalRead(ledRed));
    }
    break;
  }
}
