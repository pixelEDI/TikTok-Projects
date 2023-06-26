#include <Arduino.h>
#include <AccelStepper.h>
#include <SPI.h>
#include <MFRC522.h>

// Motor
const int dirPin = 16;
const int stepPin = 17;

#define motorInterfaceType 1 // for extern stepper driver

AccelStepper candyStepper(motorInterfaceType, stepPin, dirPin);

// RFID
const int SS_PIN = 26;
const int RST_PIN = 5;
MFRC522 rfid(SS_PIN, RST_PIN);

void ReadUidByte()
{
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  if (content.substring(1) == "23 30 C1 BE")
  {

    Serial.println("Skittles marsch");
    candyStepper.move(200);
  }
}

void setup()
{
  Serial.begin(115200);
  SPI.begin();     // start SPI bus
  rfid.PCD_Init(); // start RFID-Modul
  Serial.println("RFID-RC522 ist bereit");
  candyStepper.setMaxSpeed(1000);
  candyStepper.setAcceleration(50);
  candyStepper.setSpeed(200);
}

void loop()
{
  candyStepper.run();

  if (candyStepper.currentPosition() == 200)
  {
    candyStepper.stop();
    candyStepper.setCurrentPosition(0);
  }

  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  ReadUidByte();
}
