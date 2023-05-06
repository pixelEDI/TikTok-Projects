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
RYS8833 GNSS Modul | V1.0 | 05.2023

*/

#include <Arduino.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial ss(2); // RX TX

void setup()
{
  Serial.begin(115200); // Initialize Serial port for debugging
  ss.begin(115200);
  delay(1500);
  ss.print("@GSTP\r\n"); // positioning stop
  delay(200);
  ss.print("@GNS 01\r\n"); // Positioning-use satellite use GPS + GLONASS + SBAS + QZSS L1-CA + QZSS L1-S
  delay(200);
  ss.print("@GSR\r\n"); // hot start
  delay(200);
  Serial.print("Setup finished");
}

void loop()
{
  while (ss.available() > 0)
  {

    // check the raw output
    // int incomingByte = ss.read();
    // Serial.print(char(incomingByte));
   
    if (gps.encode(ss.read())) {

      if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(", Longitude: ");
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println("No GPS data available");
      }
    }
  }

}
