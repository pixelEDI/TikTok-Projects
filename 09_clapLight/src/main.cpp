/*

        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | www.linktr.ee/pixeledi
ClapLight | V1.0 | 10.2022

*/

#include <Arduino.h>
const byte LEDred = 7;
const byte LEDgreen = 6;
const byte LEDblue = 5;
const byte soundModul = 13;

unsigned int clap = 0;
unsigned long detection_range_start = 0;
unsigned long detection_range = 0;

void colourToLed(byte red, byte green, byte blue)
{
  analogWrite(LEDred, red);
  analogWrite(LEDgreen, green);
  analogWrite(LEDblue, blue);
}

void setup()
{
  pinMode(soundModul, INPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  pinMode(LEDred, OUTPUT);
  colourToLed(0, 0, 0);
}

void detectTwoClapsInTimeWindow(unsigned int timeWindow2ndClap)
{

  int status_sensor = digitalRead(soundModul);
  if (status_sensor == HIGH)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    // 2nd clap must be greater than 300ms
    else if (clap > 0 && millis() - detection_range >= timeWindow2ndClap)
    {
      detection_range = millis();
      clap++;
    }
  }
}

void loop()
{

  detectTwoClapsInTimeWindow(300);

  // if first clap and 2nd clap inside x second timewindows -> go on
  if (millis() - detection_range_start >= 1000)
  {
    static byte cnt = 0;
    if (clap == 2)
    {
      switch (cnt)
      {
      case 0:

        colourToLed(255, 255, 0); // yellow
        cnt++;
        break;

      case 1:
        colourToLed(255, 0, 0); // red
        cnt++;
        break;

      case 2:
        colourToLed(255, 0, 255); // pink
        cnt++;
        break;

      case 3:
        colourToLed(0, 0, 255); // blue
        cnt++;
        break;

      case 4:
        colourToLed(0, 255, 255); // turquois
        cnt++;
        break;

      case 5:
        colourToLed(0, 255, 0); // green
        cnt++;
        break;

      default:
        // reset
        colourToLed(0, 0, 0); // black
        cnt = 0;
      }
    }

    // reset claps if clap <2
    clap = 0;
  }
}