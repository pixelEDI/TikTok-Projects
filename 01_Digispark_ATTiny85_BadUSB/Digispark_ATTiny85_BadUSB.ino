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
  ATTiny85 Digispark Bad USB | V1.0 | 09/2022

*/

#include "DigiKeyboard.h"

void setup() {
  // don't need to set anything up to use DigiKeyboard
  DigiKeyboard.update();
}


void loop() {
  
  DigiKeyboard.update();
  delay(100);
  
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); // meta+r
  delay(100);
  DigiKeyboard.println("notepad");
  delay(200);
  //y + z switched :)
  DigiKeyboard.println("Hello from ATTINY!");
  
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(5000);
}
