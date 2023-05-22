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
REYAX RYRR10S 13.56MHz RFID & NFC Antenna Module  | V1.0 | 05.2023

*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, OLED_ADDR);

// Software Serial
SoftwareSerial rfid(4, 5); // RX, TX

uint8_t received_buf_pos = 0;
uint8_t response_byte;
String tag_id = "";
char Byte_In_Hex[3];
bool cooldown = false;
unsigned long previousMillis = millis();

// Serial Commands ST CR95HF or RYRR10S
uint8_t echo_command[1] = {0x55};
uint8_t initialise_cmd_iso14443_1[6] = {0x09, 0x04, 0x68, 0x01, 0x07, 0x10};
uint8_t initialise_cmd_iso14443_2[6] = {0x09, 0x04, 0x68, 0x01, 0x07, 0x00};
uint8_t initialise_cmd_iso14443_3[6] = {0x02, 0x04, 0x02, 0x00, 0x02, 0x80};
uint8_t initialise_cmd_iso14443_4[6] = {0x09, 0x04, 0x3A, 0x00, 0x58, 0x04};
uint8_t initialise_cmd_iso14443_5[6] = {0x09, 0x04, 0x68, 0x01, 0x01, 0xD3};

uint8_t detect_cmd_iso14443_1[4] = {0x04, 0x02, 0x26, 0x07};
uint8_t detect_cmd_iso14443_2[5] = {0x04, 0x03, 0x93, 0x20, 0x08};

void show_serial_data()
{
  while (rfid.available() != 0)
    Serial.print(rfid.read(), HEX);
  Serial.println("");
}

// Initialize the RYRR10S RFID module with sequence of commands given in datasheet
// to configure the RFID module as UID Reader
void initRFID()
{
  rfid.begin(57600);
  delay(500);
  Serial.println("Echo command: ");
  rfid.write(echo_command, 1);
  delay(100);
  show_serial_data();
  Serial.println("Initialise commands: ");
  rfid.write(initialise_cmd_iso14443_1, 6);
  delay(100);
  show_serial_data();
  rfid.write(initialise_cmd_iso14443_2, 6);
  delay(100);
  show_serial_data();
  rfid.write(initialise_cmd_iso14443_3, 6);
  delay(100);
  show_serial_data();
  rfid.write(initialise_cmd_iso14443_4, 6);
  delay(100);
  show_serial_data();
  rfid.write(initialise_cmd_iso14443_5, 6);
  delay(100);
  show_serial_data();
  delay(200);
  Serial.println("RFID Ready");
}

void readTag()
{
  uint8_t received_char;
  while (rfid.available() != 0)
  {
    received_char = char(rfid.read());

    if (received_buf_pos == 0)
    {
      response_byte = received_char;
      // Serial.print(rfid.read(), HEX);
      // Serial.println("------");
    }
    else
    {
      // Serial.print(rfid.read(), HEX);
      sprintf(Byte_In_Hex, "%x", received_char);
      tag_id += Byte_In_Hex;
    }
    received_buf_pos++;
  }

  if (response_byte == 0x80)
  {

    // Serial.print("response_byte");
    // Serial.println((response_byte), HEX);
    //--------- show UID from card/chip ----------------------
    // Serial.print("Tag id: ");
    // Serial.println(tag_id);

    if (tag_id == "5402800808f3149b92ee2800")
    {
      Serial.println("blue chip");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Blue Chip");
      cooldown = true;
    }
    else if (tag_id == "5402800808a4325660a02800")
    {
      Serial.println("white card");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("white card");
      cooldown = true;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();      
  display.setTextSize(1);      
  display.setTextColor(WHITE); 
  display.setCursor(20, 20);   
  display.println("Hello TikTok");  
  display.display(); // Display the content on the OLED screen

  initRFID();
}

void loop()
{
  // Serial.println("Start searching new card");
  rfid.write(detect_cmd_iso14443_1, 4);
  delay(800);
  // Serial.println("Response:");
  // show_serial_data();
  rfid.write(detect_cmd_iso14443_2, 5);
  delay(300);

  if (rfid.available())
  {
    readTag();
    // reset global variables
    received_buf_pos = 0;
    response_byte = 0;
    tag_id = "";
  }

  //cooldown - only one card every x seconds
  if (cooldown)
  {
    cooldown = false;
    Serial.println("Cooldown activated");
    delay(1000 * 3);
    Serial.println("Cooldown finished");
  }
}
