/*


        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | twitter.com/pixeledi
Electronic SAFE | V1.0 | 09.2022

*/

#include <Arduino.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <fastLED.h>

// for MQTT
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "credentials.h"

String clientId = "ESP32-";
const char *mqtt_server = "192.168.178.x";
const char *mqtt_user = "";
const char *mqtt_password = "";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// RFID
const int SS_PIN = 5;
const int RST_PIN = 27;
MFRC522 rfid(SS_PIN, RST_PIN);

// motor
const int servoPin = 2;
Servo myservo;

// leds
const int NUM_LEDS = 7;
const int DATA_PIN = 25;
CRGB leds[NUM_LEDS];
int randomRed = 0;
int randomGreen = 0;
int randomBlue = 0;
const int LEDRed = 4;

bool dooropen = false;

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      // Subscribe
      // client.subscribe("topic");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// only required if we get informations from mqtt

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "topic")
  {
    // action
  }
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

    if (cnt > 30)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  pinMode(LEDRed, OUTPUT);
  SPI.begin();     // start SPI bus
  rfid.PCD_Init(); // start RFID-Modul
  Serial.println("RFID-RC522 ist bereit");

  myservo.attach(servoPin);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32Tresor");

  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.println();
  // read the RFID-tags
  Serial.print(" UID tag  :");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  Serial.print(" PICC type: ");
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // the returned hex-value can be used for further actions

  Serial.println(rfid.PICC_GetTypeName(piccType));

  if (content.substring(1) == "AC 32 E6 8C")
  {

    if (dooropen)
    {
      myservo.write(90); // move MG996R's shaft to angle 0°
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].setRGB(0, 0, 0); // leds off
      }
      FastLED.setBrightness(50);
      FastLED.show();
      dooropen = false;
      delay(1000);
    }

    else if (dooropen == false)
    {
      myservo.write(0); // move MG996R's shaft to angle 90°
      randomRed = random(1, 256);
      randomBlue = random(1, 256);
      randomGreen = random(1, 256);

      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].setRGB(randomRed, randomGreen, randomBlue); // leds on with random colours
      }
      FastLED.setBrightness(50);
      FastLED.show();
      client.publish("safe", "Your safe has been opened"); // E-Mail
      dooropen = true;
      delay(1000);
    }
  }
  else
  {
    digitalWrite(LEDRed, HIGH);
    delay(1000);
    digitalWrite(LEDRed, LOW);
    delay(1000);
  }
}
