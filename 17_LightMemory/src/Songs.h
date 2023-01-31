#ifndef songs_h
#define songs_h

#include <Arduino.h>
#include "pitches.h"

class Songs
{
private:
    int musicLength;
    byte buzzer;
    byte *noteDurationSong;
    uint16_t *melody;


public:
    Songs(byte *_noteDurationSong, uint16_t *_melody, byte _buzzer, int _musicLength);
    void playMusic();
};

#endif