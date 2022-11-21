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
Zeiterfassung via MQTT | V1.0 | 11.2022

*/
#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

// RFID
const int SS_PIN = 26;
const int RST_PIN = 5;
MFRC522 rfid(SS_PIN, RST_PIN);

// for MQTT
#include <PubSubClient.h>
#include <WiFi.h>
#include "credentials.h"

const byte led = 22;

// MQTT
String clientId = "ESP32-";
//mqtt credentials -> credentials.h
//const char *mqtt_server = "";
//const char *mqtt_user = "";
//const char *mqtt_password = "";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

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
      // for this example not necessary
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

  Serial.begin(115200); // Initialize serial communications with the PC
  SPI.begin();          // start SPI bus
  rfid.PCD_Init();      // start RFID-Modul
  Serial.println("RFID-RC522 ist bereit");

  pinMode(led, OUTPUT);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

/**
 * Main loop.
 */
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32Zeiterfassung");

  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  // Serial.println();
  // // read the RFID-tags
  // Serial.print(" UID tag  :");
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

  // Serial.println(rfid.PICC_GetTypeName(piccType));

  if (content.substring(1) == "43 45 43 AC")
  {
    Serial.println("mqtt azw");
    client.publish("zeiterfassung/inktammy", "#TikTok"); 
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
  }
  else if (content.substring(1) == "F3 14 9B 92")
  {
    Serial.println("mqtt pixeledi");
    client.publish("zeiterfassung/inktammy", "#school"); 
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
  }
}
