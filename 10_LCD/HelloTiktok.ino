#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

char hello[13] = {'h', 'e', 'l', 'l', 'o', ' ', 'T', 'i', 'k', 'T', 'o', 'k'};

char GitHub[22] = {'g', 'e', 't', ' ', 'm', 'y', ' ', 'c', 'o', 'd', 'e', ' ', 'o', 'n', ' ', 'G', 'i', 't', 'H', 'u', 'b'};

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.cursor();
  for (int i = 0; i < 12; i++) {

    lcd.print(hello[i]);

    delay(500);

  }

  lcd.setCursor(16, 1);
  lcd.noCursor();
  lcd.autoscroll();
  for (int i = 0; i < 21; i++) {

    lcd.print(GitHub[i]);

    delay(500);

    if (i== 20){
      delay(1000);
    }

  }

  lcd.noAutoscroll();
  
  // clear screen for the next loop:
  lcd.clear();
}
