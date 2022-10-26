#include <Arduino.h>
#include <Wire.h>             // for the ToF Sensor
#include <VL53L0X.h>          // for the ToF Sensor
#include <Adafruit_GFX.h>     // for the oled Display
#include <Adafruit_SSD1306.h> // for the oled Display

int btn = 16;
int laser = 17;

// FoT Sensor
VL53L0X sensor;
unsigned int measurement;

// Oled Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void showMeasurement()
{
  measurement = sensor.readRangeSingleMillimeters();
  display.clearDisplay();
  analogWrite(laser, 255);

  if (measurement >= 10 && measurement < 100)
    display.setCursor(36, 0);

  else if (measurement >= 100 && measurement < 1000)
    display.setCursor(18, 0);

  else
    display.setCursor(0, 0);

  display.print(measurement);
  display.setCursor(92, 0);
  display.print("mm");
  display.display();
}

void setup()
{
  Serial.begin(115200);
  pinMode(btn, INPUT);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1)
    {
      // I will stay here foreveeeeer :(
    }
  }
  sensor.setMeasurementTimingBudget(200000); // increase timing budget to 200 ms for more accuracy
}

void loop()
{
  if (digitalRead(btn) == HIGH)
  {
    showMeasurement();
  }

  if (digitalRead(btn) == LOW){
    analogWrite(laser, 0); 
  }
}