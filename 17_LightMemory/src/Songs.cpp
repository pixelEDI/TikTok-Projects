#include <Arduino.h>
#include "Songs.h"
#include "pitches.h"
#include "TimerFreeTone.h"

Songs::Songs(byte *_noteDurationSong, uint16_t *_melody, byte _buzzer, int _musicLength){
    melody= _melody;
    noteDurationSong = _noteDurationSong;
    buzzer=_buzzer;

    pinMode(buzzer, OUTPUT);
    musicLength = _musicLength;
}

void Songs::playMusic(){

    for (int thisNote = 0; thisNote < musicLength; thisNote++)
    {
      int noteDuration = 2000 / noteDurationSong[thisNote];
      TimerFreeTone(buzzer, melody[thisNote], noteDuration, 10); // Play melody[thisNote] for duration[thisNote].

      delay(50);
     }
    delay(100);
}

