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
Keypad & LCD | V1.0 | 10.2022

Keypad Example from Library Chris--A:
https://github.com/Chris--A/Keypad/blob/master/examples/CustomKeypad/CustomKeypad.ino

*/

#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int pwTries = 1;
bool pwEnter = true;
bool lcdEmpty = true;

const byte ROWS = 4; //four rows
const byte COLUMNS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLUMNS] = {6,7,A1,A0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLUMNS );

const String password = "1234"; // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  input_password.reserve(32); // maximum input characters is 33, change if needed
}

void loop() {
  char key = keypad.getKey();

  if (pwEnter) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ENTER");
    lcd.setCursor(4, 1);
    lcd.print("PASSWORD");
    pwEnter = false;
  }

  if (key) {
    if (lcdEmpty) {
      lcd.clear();
      lcdEmpty = false;
    }

    if (key != '*' && key != '#') {
      lcd.print("*");
    }

    if (key == '*') {
      input_password = ""; // clear input password
      pwEnter = true;
      lcdEmpty = true;

    } else if (key == '#') {
      if (password == input_password) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("PASSWORD IS");
        lcd.setCursor(4, 1);
        lcd.print("CORRECT");
        pwEnter = true;
        lcdEmpty = true;
        delay(2000);
        // DO YOUR WORK HERE

      } else {

        switch (pwTries) {
          case 1:
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("WRONG PASSWORD");
            lcd.setCursor(3, 1);
            lcd.print("TRY AGAIN");
            lcdEmpty = true;
            pwTries ++;
            break;
          case 2:
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("WRONG PASSWORD");
            lcd.setCursor(0, 1);
            lcd.print("ONE ATTEMPT LEFT");
            lcdEmpty = true;
            pwTries ++;
            break;
          case 3:
            for (int i = 0; i < 10; i++) {
              lcd.clear();
              lcd.setCursor(1, 0);
              lcd.print("WRONG PASSWORD");
              lcd.setCursor(0, 1);
              lcd.print("LOCKED FOR");
              lcd.setCursor(11, 1);
              lcd.print(10 - i);
              lcd.print(" s");
              delay(1000);
            }
            pwTries = 1;
            pwEnter = true;
            lcdEmpty = true;
            break;
        }

      }

      input_password = ""; // clear input password

    } else {
      input_password += key; // append new character to input password string
    }
  }
}
