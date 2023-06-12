
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "credentials.h"
#include "globals.h"

String checkUser(String txt)
{
  String returnTxt = "";
  if (String(txt) == "1")
    returnTxt = "T";
  else
    returnTxt = "E";

  return returnTxt;
}

void makeStats(int row, String _who, String _moves, String _solvingtime)
{
  String txt = "  " + _who + " | " + _solvingtime + " | " + _moves;
  if (row == 1)
    stats1 = row + txt;
  else if (row == 2)
    stats2 = row + txt;
  else if (row == 3)
    stats3 = row + txt;
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.subscribe("cube/showToplist/timer");
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

void callbackmqtt(char *topic, byte *message, unsigned int length)
{
  // Serial.print("Message arrived on topic: ");
  // Serial.print(topic);
  // Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    // Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  // Serial.println();

  if (String(topic) == "cube/showToplist/timer")
  {

    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, messageTemp);

    if (error)
    {
      // Serial.print("deserializeJson() failed: ");
      // Serial.println(error.c_str());
      return;
    }

    JsonObject root_0 = doc[0];
    const char *root_0_wer = root_0["wer"];                 // "1"
    const char *root_0_zeitstempel = root_0["zeitstempel"]; // "31.3.23"
    int root_0_solvingtime = root_0["solvingtime"];         // 656
    int root_0_moves = root_0["moves"];                     // 3

    JsonObject root_1 = doc[1];
    const char *root_1_wer = root_1["wer"];                 // "1"
    const char *root_1_zeitstempel = root_1["zeitstempel"]; // "31.3.23"
    int root_1_solvingtime = root_1["solvingtime"];         // 1010
    int root_1_moves = root_1["moves"];                     // 3

    JsonObject root_2 = doc[2];
    const char *root_2_wer = root_2["wer"];                 // "1"
    const char *root_2_zeitstempel = root_2["zeitstempel"]; // "31.3.23"
    int root_2_solvingtime = root_2["solvingtime"];         // 1076
    int root_2_moves = root_2["moves"];                     // 5

    int root_3_rank = doc[3]["rank"]; // 5
    int root_3_cnt = doc[3]["cnt"];   // 14

    String time1 = convertMillisToReadableTime(root_0_solvingtime);
    String time2 = convertMillisToReadableTime(root_1_solvingtime);
    String time3 = convertMillisToReadableTime(root_2_solvingtime);

    makeStats(1, checkUser(String(root_0_wer)), time1, String(root_0_moves));
    makeStats(2, checkUser(String(root_1_wer)), time2, String(root_1_moves));
    makeStats(3, checkUser(String(root_2_wer)), time3, String(root_2_moves));

    String time4 = convertMillisToReadableTime(solvingTime);
    lastStats = String(root_3_rank) + "/" + String(root_3_cnt) + "|" + moves + "|" + time4;

    showStats();
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
