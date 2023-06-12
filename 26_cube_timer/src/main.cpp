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
Cube Timer ESP32 | V1.0 | 04.2023

*/

#include <Arduino.h>
#include <Wire.h>
#include "globals.h"
#include "button.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "batterygrafic.h"
#include "oled.h"
#include "wifimqtt.h"


Button rndBTN(4);

void newRound()
{
  showReady();
  solved = false;
  firstStart = false;
  moves = 0;
  startTime = millis();
 //Serial.println("new Round started");
}

void readBatteryVoltage()
{
  if (millis() - millisBattery > (1000 * 10))
  {
    millisBattery = millis();

    uint32_t Vbatt = 0;
    for (int i = 0; i < 16; i++)
    {
      Vbatt = Vbatt + analogReadMilliVolts(A0); // ADC with correction
    }
    // voltage divider actual with 2x 100kOhm to A0
    // results in Voltage / 2
    // get rid of the spikes ->for loop with 16 
    // calculate voltage
    Vbattf = 2 * Vbatt / 16 / 1000.0; 

    // Serial.println(Vbattf, 3);
  }
}

void isPressureSensorSmashed()
{
  int val = analogRead(pressureSensor);

  //Serial.println(val);

  if (val >= 1000 && !solved)
  {
    solved = true;
    //Serial.println(solvingTime);

    DynamicJsonDocument doc(128);
    doc["wer"] = user;
    doc["solvingtime"] = solvingTime;
    doc["moves"] = moves;

    char buffer[128];
    serializeJson(doc, buffer);

    client.publish("cube/newRound/timer", buffer);
    solved = true;
  }
}

void isButtonClicked()
{

  switch (rndBTN.checkBTN())
  {
  case 1:
    newRound();
    break;
  case 2:
    //Serial.println("change user");
    if (user == 1)
      user = 2;
    else
      user = 1;
  };
}

void setup()
{
  // Serial.begin(115200);

  rndBTN.start();
  pinMode(pressureSensor, INPUT);

  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display1.clearDisplay();
  showFirstStart();
  solved = false;

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callbackmqtt);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32Cube_Timer");

  isButtonClicked();
  isPressureSensorSmashed();
  readBatteryVoltage();

  if (!solved && !firstStart)
  {
    firstStart = false;
    solvingTime = (millis() - startTime);

    showOled();
  }

  // if (solved)
  // {
  //   // oled is changed from mqtt callback
  // }
}