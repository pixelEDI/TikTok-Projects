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
MAX72xx Panel | V1.0 | 05.2023
*/
#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>

unsigned long previousMillis = millis();

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
// all other Pins are SPI Pins from ESP32
#define CS_PIN 20
MD_Parola mx = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// other Variants
// https://majicdesigns.github.io/MD_Parola/class_m_d___parola.html

#define BUF_SIZE 75
char pxMessage[BUF_SIZE] = {"pixelEDI"};

void setup()
{
  Serial.begin(115200);

  mx.begin();
  mx.setIntensity(2);
  mx.displayClear();
  mx.displayScroll(pxMessage, PA_RIGHT, PA_SCROLL_LEFT, 60);

  Wire.begin();

  Serial.println("Setup finished");
}

void loop()
{

  // first example
  // mx.setTextAlignment(PA_LEFT);
  // mx.print("ESP32");

  if (mx.displayAnimate())
  {
    mx.displayReset();
  }
}
