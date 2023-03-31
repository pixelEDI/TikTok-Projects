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
JoyStick mit LEDs| V1.0 | 09.2022

*/

#include <Arduino.h>

const byte XCoordinate = A1;
const byte YCoordinate = A0;
const byte ZButton = 5;

const byte ledLeft = 6;
const byte ledDown = 7;
const byte ledMiddle = 8;
const byte ledUp = 9;
const byte ledRight = 10;

int left = 800;  // JoySticks works with 
int right = 400; // two potentiometer from 0-1023
int up = 800;    // so you need treshholds 
int down = 400;  // for x and y coordinates

void setup()
{
  Serial.begin(115200);
  pinMode(XCoordinate, INPUT);
  pinMode(YCoordinate, INPUT);
  pinMode(ZButton, INPUT_PULLUP);

  pinMode(ledDown, OUTPUT);
  pinMode(ledUp, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledMiddle, OUTPUT);
}

void AllLedsLow()
{
  digitalWrite(ledDown, LOW);
  digitalWrite(ledUp, LOW);
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledMiddle, LOW);
}

void loop()
{
  int xValue = analogRead(XCoordinate);
  int yValue = analogRead(YCoordinate);
  int zValue = digitalRead(ZButton);

  AllLedsLow();

  if (xValue > left)
  {
    digitalWrite(ledLeft, HIGH);
  }

  else if (xValue < right)
  {
    digitalWrite(ledRight, HIGH);
  }

  if (yValue > up)
  {
    digitalWrite(ledUp, HIGH);
  }

  else if (yValue < down)
  {
    digitalWrite(ledDown, HIGH);
  }

  if (zValue == LOW)
  { // LOW because it's defined as pullup
    digitalWrite(ledMiddle, HIGH);
  }
}