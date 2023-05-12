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
E-INK 3C | V1.0 | 05.2023

convert grafics:
https://javl.github.io/image2cpp/

// ESP wiring
// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN / SDI -> MOSI(23), GND -> GND, 3.3V -> 3.3V
*/

#include <Arduino.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/TomThumb.h>
#include "eink_image.h"
#include "credentials.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define MAX_DISPLAY_BUFFER_SIZE 800

#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
GxEPD2_3C<GxEPD2_290c, MAX_HEIGHT_3C(GxEPD2_290c)> display(GxEPD2_290c(/*CS=*/5, /*DC=*/17, /*RST=*/16, /*BUSY=*/4)); // GDEW029Z10 128x296, UC8151 (IL0373

unsigned long previousMillis = 0;
String serverName = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cdogecoin&vs_currencies=eur";

String bitcoin;
String dogecoin;

String nextWord(String x)
{
  return x.substring(0, x.indexOf(' '));
}

void connectAP()
{
  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 20)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}

void getCryptos()
{
  Serial.println("Getting Cryptos...");
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(serverName.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      // Serial.println(payload);

      // JSON Output from https://arduinojson.org/v6/assistant

      StaticJsonDocument<128> doc;

      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      for (JsonPair item : doc.as<JsonObject>())
      {
        const char *item_key = item.key().c_str(); // "bitcoin", "dogecoin"

        float value_eur = item.value()["eur"]; // 24141, 0.065028

        if (item.key() == "dogecoin")
        {
          Serial.println("dogecoin");
          dogecoin = String(value_eur);
          Serial.println(value_eur);
        }
        else if (item.key() == "bitcoin")
        {
          Serial.println("bitcoin");
          bitcoin = String(int(value_eur)); // no commas
          Serial.println(value_eur);
        }
      }
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("Reconnect to AP");
    connectAP();
  }
}

void showImage()
{
  display.setRotation(1);
  display.setFullWindow();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, bitcoind_dogecoin_icon, 296, 128, GxEPD_RED);
  } while (display.nextPage());
}

void updateDogecoin()
{
  int box_x = 145;
  int box_y = 60;
  int box_w = 140;
  int box_h = 30;
  display.setPartialWindow(box_x, box_y, box_w, box_h);
  display.firstPage();
  do
  {
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    display.setCursor(box_x + 40, box_y + 30);
    Serial.println(dogecoin);
    display.print(dogecoin);
  } while (display.nextPage());
}

void updateBitcoin()
{
  int box_x = 5;
  int box_y = 60;
  int box_w = 140;
  int box_h = 30;
  display.setPartialWindow(box_x, box_y, box_w, box_h);
  display.firstPage();
  do
  {
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    display.setCursor(box_x + 40, box_y + 30);
    display.print(bitcoin);
  } while (display.nextPage());
}

void lastRow()
{
  int box_x = 5;
  int box_y = 118;
  int box_w = 290;
  int box_h = 8;
  display.setPartialWindow(box_x, box_y, box_w, box_h);
  display.setFont(&TomThumb);

    display.setTextColor(GxEPD_RED);
  do
  {
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
      display.setCursor(box_x, box_y);
    display.print("check out my code on github.com/pixeledi");
  } while (display.nextPage());
}

void updateCoins()
{
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(GxEPD_BLACK);

  updateBitcoin();
  updateDogecoin();
}

void setup()
{
  Serial.begin(115200);
  connectAP();

  display.init(115200);
   showImage();
  delay(1000);

  getCryptos();
  updateCoins();
  lastRow();

  display.hibernate();
}

void loop()
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 * 60 * 1)
  {
    previousMillis = currentMillis;

    getCryptos();
    updateCoins();
    Serial.println("E-Ink updated");
  }
}