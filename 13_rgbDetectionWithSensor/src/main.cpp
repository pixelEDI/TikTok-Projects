/*
         _          _ ______ _____ _____
        (_)        | |  ____|  __ \_   _|
   _ __  ___  _____| | |__  | |  | || |
  | '_ \| \ \/ / _ \ |  __| | |  | || |
  | |_) | |>  <  __/ | |____| |__| || |_
  | .__/|_/_/\_\___|_|______|_____/_____|
  | |
  |_|

  ColorWheel | V1.1 | 11/2022
  color sensor library from Adafruit https://github.com/adafruit/Adafruit_TCS34725
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <fastLED.h>

// leds
const int NUM_LEDS = 12;
const int DATA_PIN = 6;
CRGB leds[NUM_LEDS];
byte gammatable[256];

//color sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  tcs.begin();

  // this gamma table converts RGB colors to what humans see
  for (int i = 0; i < 256; i++)
  {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x;
  }
}

void loop()
{
  float red, green, blue;

  tcs.getRGB(&red, &green, &blue);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(gammatable[(int)red], gammatable[(int)green], gammatable[(int)blue]);
  }

  FastLED.setBrightness(20);
  FastLED.show();
  delay(10);
}