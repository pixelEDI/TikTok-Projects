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
  Seeed Stduio XIAO ESP32C3 with MQTT | V1.0 | 09/2022

*/
#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "credentials.h"

#define DHTPIN 10 // D10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
unsigned long previousMillis = 0;
byte led = 3;

// static IP  Address
IPAddress local_IP(192, 168, 178, 100);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

// MQTT Stuff
String clientId = "ESP32-";
const char *mqtt_server = "192.168.178.02";
const char *mqtt_user = "";
const char *mqtt_password = "";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

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
      client.subscribe("ledXIAO");
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

  if (String(topic) == "ledXIAO")
  {
    Serial.println(messageTemp);
    if (messageTemp=="on")
      digitalWrite(led, HIGH);
    else if(messageTemp=="off")
      digitalWrite(led, LOW);
  }
}

void connectAP()
{
  // Statische IP-Adresse
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
  }

  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 20)
      break;
  }
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(led, OUTPUT);
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("myTempData");

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    float hum = dht.readHumidity();
    float tempC = dht.readTemperature();
    // a Broker has to subscribe to these topics
    client.publish("tempValues", String(tempC).c_str());
    delay(10);
    client.publish("humValues", String(hum).c_str());
 
  }
}