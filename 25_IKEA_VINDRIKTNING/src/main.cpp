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
UART with ESP32 / IKEA VINDRIKTNING | V1.0 | 05.2023
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialESP(D2, D3); //D2 = RX, D3 not used
byte buff[20];
byte rxId=0;

void setup()
{
  Serial.begin(115200); // Serial Monitor
  SerialESP.begin(9600);
  Serial.println("Setup finished");
}

void loop()
{

  if(SerialESP.available()){
    while(SerialESP.available()){
      buff[rxId++]=SerialESP.read();
      Serial.print("~");
    }

    if(rxId>=20){
      int pm25 = buff[5]*256+buff[6];
      Serial.println(pm25);
      rxId=0;
    }
  }

}
