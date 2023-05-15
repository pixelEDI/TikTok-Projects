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
REYAX Bluetooth module with Arduino UNO | V1.0 | 05/2023
*/

#include <SoftwareSerial.h>

SoftwareSerial BTserial(4, 5);  // RX, TX
String BTData = "";
String ArduinoData = "";

// Android Bluetooth Terminal
// First pairing
// in Bluetooth Terminal APP "edit" Device and fetch Data for UUID etc.
// choose the follwing IDS according Reyax Datasheet: https://reyax.com//products/RYBG211_lite
// Service UUID: 4880c12c-fdcb-4077-8920-a450d7f9b907
// Write & Notification UUID: fec26ec4-6d71-4442-9f81-55bc21d658d6

// AT Commands
// AT
// AT+ADDR?
// Send to bluetooth terminal a message
// AT+SEND=<Connection>,< Length>,<Data>
// AT+SEND=1,5,HELLO

String getMessage(String input) {
  String message;
  int firstComma = input.indexOf(",");                   // find the first comma
  int secondComma = input.indexOf(",", firstComma + 1);  // find the second comma

  if (firstComma != -1 && secondComma != -1) {   // check if all commas were found
    message = input.substring(secondComma + 1);  // extract the message value
    message.trim();                              // remove whitespaces
  }
  return message;
}

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  Serial.println("Setup finished");
}

void loop() {
if (BTserial.available()) {
  BTData = BTserial.readString();
  // process Message which we get in this format: +RCV=1,9,mymessage

  Serial.print(BTData);
  String tmpData = getMessage(BTData);
  Serial.print(tmpData);

  // ---- here you can process the incoming message ----
  // if(tmpData=="my bluetoothmessage"){
  //   Serial.println("do something");
  // }
  // else {
  //   Serial.println("not allowed");
  // }
}
}
