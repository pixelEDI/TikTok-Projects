#include <Arduino.h>
#include <TM1637Display.h>
#include "button.h"
#include "pitches.h"
#include "TimerFreeTone.h"
#include "Songs.h"

// 7 segment display
const int CLK = 13;
const int DIO = 12;
TM1637Display display(CLK, DIO);

const uint8_t SEGEMENT_round[] = {
    SEG_E | SEG_G,
    SEG_G | SEG_E | SEG_D | SEG_C | SEG_B,
    SEG_DP, // blank
    SEG_DP  // blank
};

// LEDs
const int LEDred = 9;
const int LEDgreen = 5;
const int LEDblue = 3;
const int LEDyellow= 6;

// buttons
Button btnRed(11);
Button btnGreen(8);
Button btnYellow(10);
Button btnBlue(7);

// Buzzer
int buzzer = 2;

// Music
uint16_t melodyWon[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4};
uint16_t melodyLost[] = {NOTE_C4, NOTE_B3, NOTE_A3, NOTE_GS3};
uint16_t melodyNext[] = {NOTE_C4, NOTE_GS4};
uint16_t melodyNewGame[] = {NOTE_D4, NOTE_D4, NOTE_GS4};

// duration
byte noteDurationWon[] = {16, 16, 16, 4, 16, 2};
byte noteDurationLost[] = {8, 8, 8, 2};
byte noteDurationNext[] = {16, 8};
byte noteDurationNewGame[] = {16,16,8};

Songs songWon(noteDurationWon, melodyWon, buzzer, 6);
Songs songLost(noteDurationLost, melodyLost, buzzer, 4);
Songs songNext(noteDurationNext, melodyNext, buzzer, 2);
Songs songNewGame(noteDurationNewGame, melodyNewGame, buzzer, 3);

// Game
String gameArray[20];
String coloursArray[4] = {"red", "blue", "green", "yellow"};
String userInput[20];

enum states
{
  STARTGAME,
  SHOWCOLORCOMBI,
  WAIT4INPUT,
  NEXTROUND,
  CHECKUSERINPUT,
  END
} state;

int rndcnt = 1;
int gamecnt = 0;
bool won = true;

void allLedsOut()
{
  analogWrite(LEDred, 0); // 220 Ohm
  analogWrite(LEDgreen, 0); // 220 Ohm
  analogWrite(LEDblue, 0); // 220 Ohm
  analogWrite(LEDyellow,0); // 220 Ohm
}

void colourToLed(String colour)
{
  allLedsOut();

  if (colour == "red")
  {
    analogWrite(LEDred, 150);
  }

  else if (colour == "blue")
  {
    analogWrite(LEDblue, 150);
  }

  else if (colour == "green")
  {
    analogWrite(LEDgreen, 80);
  }

  else if (colour == "yellow")
  {
    analogWrite(LEDyellow, 150);
  }
}

void gameStart()
{
  songNewGame.playMusic();
  rndcnt = 1;
  gamecnt = 0; 
  display.clear();
  display.setSegments(SEGEMENT_round);
  display.showNumberDecEx(rndcnt, true, false, 1, 3);

  for (int i = 0; i < 20; i++)
  {
    gameArray[i] = coloursArray[random(4)];
  }
  state = SHOWCOLORCOMBI;
}

void colourCombi()
{
  for (int i = 0; i < rndcnt; i++)
  {
    colourToLed(gameArray[i]);
    delay(700);
    allLedsOut();
    delay(300);
  }
}

void checkButtonPressed()
{
  if (btnBlue.isPressed())
  {
    userInput[gamecnt] = "blue";
    state = CHECKUSERINPUT;
  }
  else if (btnGreen.isPressed())
  {
    userInput[gamecnt] = "green";
    state = CHECKUSERINPUT;
  }

  else if (btnYellow.isPressed())
  {
    userInput[gamecnt] = "yellow";
    state = CHECKUSERINPUT;
  }

  else if (btnRed.isPressed())
  {
    userInput[gamecnt] = "red";
    state = CHECKUSERINPUT;
  }
}

void checkColourOrder()
{
  if (gameArray[gamecnt] == userInput[gamecnt])
  {
    gamecnt++;
    state = WAIT4INPUT;
  }
  else
  {
    // bUZZER
    won = false,
    state = END;
  }

  if (gamecnt == rndcnt)
  {
    state = NEXTROUND;
  }
}

void startNextRound()
{
  songNext.playMusic();
  rndcnt++;
  gamecnt = 0;

  if (rndcnt < 10)
  {
    display.showNumberDecEx(rndcnt, false, false, 1, 3);
  }

  else if (rndcnt >= 10)
  {
    display.showNumberDecEx(rndcnt, false, false, 2, 2);
  }

  if (rndcnt == 21)
  {
    state = END;
  }
  state = SHOWCOLORCOMBI;
}

void checkGameResult()
{
  if (won)
  {
    songWon.playMusic();
    state = STARTGAME;
  }

  else if (!won)
  {
    songLost.playMusic();
    delay(1000);
    state = STARTGAME;
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LEDblue, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDyellow, OUTPUT);

  display.setBrightness(7); // 0-7

  randomSeed(analogRead(0));

  state = STARTGAME;
}

void loop()
{

  switch (state)
  {
  case STARTGAME:
    gameStart();
    break;
  case SHOWCOLORCOMBI:
    colourCombi();
    state = WAIT4INPUT;
    break;

  case WAIT4INPUT:
    checkButtonPressed();
    break;

  case CHECKUSERINPUT:
    checkColourOrder();
    break;

  case NEXTROUND:
    startNextRound();
    break;

  case END:
    checkGameResult();
    break;
  }
}
