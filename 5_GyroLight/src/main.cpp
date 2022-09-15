#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <fastLED.h>

Adafruit_MPU6050 mpu;

float xtreshhold = 0.0;
float ytreshhold = 0.0;
float ztreshhold = 0.0;

#define NUM_LEDS 7
#define DATA_PIN 25

CRGB leds[NUM_LEDS];

void setTreshholds()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  xtreshhold = (a.acceleration.x);
  ytreshhold = (a.acceleration.y);
  ztreshhold = (a.acceleration.z);
}

void setup(void)
{
  Serial.begin(115200);
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (true)
    {
    }
  }
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{

  setTreshholds();

  if (ztreshhold <= -4.5) // DOWN
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 0, 0); // RED
    }
  }

  else if (ztreshhold >= 4.5) // UP
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 0); // GREEN
    }
  }

  else if (xtreshhold <= -4.5) // LEFT
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 0, 255); // BLUE
    }
  }

  else if (xtreshhold >= 4.5) // RIGHT
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 255, 0); // YELLOW
    }
  }

  else if (ytreshhold <= -4.5) // FRONT
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 255); // TURQUIS
    }
  }

  FastLED.setBrightness(50);
  FastLED.show();
}
