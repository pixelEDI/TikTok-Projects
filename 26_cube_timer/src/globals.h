#ifndef globals_h
#define globals_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_SH110X.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//Adafruit_SH1106G display1 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

byte pressureSensor =A3;

bool solved = false;
bool firstStart = true;
int moves = 0;
unsigned long solvingTime = 0;
unsigned long startTime = 0;
byte user = 1;
unsigned long millisBattery = 0;
float Vbattf = 0;


//stats
String stats1="", stats2="", stats3 ="", lastStats="";

// MQTT
String clientId = "ESP32-";
const char *mqtt_server = "192.168.178.1";
const char *mqtt_user = "DomCobb";
const char *mqtt_password = "nooneknows";;
WiFiClient espClient;
PubSubClient client(espClient);

#endif
