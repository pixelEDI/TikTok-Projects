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
  VL53LXX-V2 on ESP32 | V1.0 | 11.2022

  SCL - GPIO 22
  SDA - GPIO 21
  GND - GND
  Vin - VCC
*/
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
unsigned int measurement;

void setup() {
  Serial.begin(115200);

  Serial.println("Start Setup");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }

  // start continuous ranging
  lox.startRangeContinuous();
  Serial.println("Start Measurment");
}

void loop() {
  //open Serial Plotter and run sketch
  if (lox.isRangeComplete()) {
    measurement = lox.readRange();
    if (measurement < 1000) {
      Serial.print("Distance in mm: ");
      Serial.println(measurement);
    }
  }
}
