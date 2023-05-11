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
DHT20 minmax | V1.0 | 05.2023
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>

// DHT22
#define DHTPIN 26
#define DHTTYPE DHT22
DHT dht22 = DHT(DHTPIN, DHTTYPE);

byte red = 18;
byte yellow = 19;
byte green = 23;

float minTemp = 5;
float maxTemp = 30;
bool threshold = false;
unsigned long thresholdTime = millis();

unsigned long previousMillis = millis();

void allLEDsOff() {
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}

void setup() {
  Serial.begin(115200);
  dht22.begin();
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= (1000 * 2)) {
    previousMillis = currentMillis;

    float temperature = dht22.readTemperature();
    float humidity = dht22.readHumidity();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read data from DHT sensor!");
      return;
    }

    // threshold test
    if (millis() > (1000 * 7)) {
      temperature = 2;
    }


    // Update minimum und maximum
    if (temperature < minTemp) {
      minTemp = temperature;
      thresholdTime = millis();
      allLEDsOff();
      digitalWrite(yellow, HIGH);
      Serial.println("Threshold min: " + String(minTemp) + " triggered after " + String(thresholdTime / 1000) + " Sec.");
      threshold = true;
    } else if (temperature > maxTemp) {
      maxTemp = temperature;
      allLEDsOff();
      digitalWrite(red, HIGH);
      thresholdTime = millis();
      Serial.println("Threshold max: " + String(maxTemp) + " triggered after " + String(thresholdTime / 1000) + " Sec.");
      threshold = true;
    }

    if (!threshold) 
     {
      allLEDsOff();
      digitalWrite(green, HIGH);
    }

    //DEBUG
    // Serial.print("Aktuelle Temperatur: ");
    // Serial.print(temperature);
    // Serial.print(" °C, Min Temperatur: ");
    // Serial.print(minTemp);
    // Serial.print(" °C, Max Temperatur: ");
    // Serial.print(maxTemp);
    // Serial.println(" °C");

    // Serial.print("Feuchtigkeit: ");
    // Serial.print(humidity);
    // Serial.println(" %");
  }
}
