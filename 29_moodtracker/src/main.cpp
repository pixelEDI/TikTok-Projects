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
Moodtracker | V1.0 | 10.2023
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "button.h"
#include "grafics.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long previousMillis = millis();
int moodtracker[4];

Button btnGreen(8);
Button btnBlue(9);
Button btnRed(10);
Button btnYellow(11);

void writeTextAndGrafic(String firstRow, String secondRow, const unsigned char *bitmapData)
{
  display.clearDisplay();
  display.drawBitmap(0, (display.height() - 50) / 2, bitmapData, 50, 50, 1);
  display.setTextSize(2);
  display.setCursor(60, 20);
  display.println(firstRow);
  display.setTextSize(1);
  display.setCursor(60, 40);
  display.println(secondRow);
  display.display();
}

void checkButtons()
{

  if (btnRed.checkBTN() == 1)
  {
    moodtracker[0]++;
    writeTextAndGrafic("Angry", String(moodtracker[0])+"x today", angry);
  }
  else if (btnBlue.checkBTN() == 1)
  {
    moodtracker[1]++;
    writeTextAndGrafic("Sad", String(moodtracker[1])+"x today", sad);
  }
  else if (btnGreen.checkBTN() == 1)
  {
    moodtracker[2]++;
    writeTextAndGrafic("Crazy", String(moodtracker[2])+"x today", crazy);
  }
  else if (btnYellow.checkBTN() == 1)
  {
    moodtracker[3]++;
    writeTextAndGrafic("Happy", String(moodtracker[3])+"x today", happy);
  }
}

void setup()
{
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  writeTextAndGrafic("Mood", "Tracker", mylogo);

  delay(100);
}

void loop()
{

  checkButtons();
}
