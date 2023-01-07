
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
Internet Radio | V1.0 | 01.2023


Library download and copy to src: 
https://github.com/schreibfaul1/ESP32-audioI2S
*/
#include "WiFi.h"
#include "Audio.h"
#include "credentials.h"

// Define I2S connections
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_LRC 25


// Create audio object
Audio audio;


void connectAP()
{

  //Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    //Serial.print(".");
    cnt++;

    if (cnt > 30)
      ESP.restart();
  }
  //Serial.println(WiFi.localIP());
}

void setup()
{

  // Start Serial Monitor
  Serial.begin(115200);

  connectAP();

  // Connect MAX98357 I2S Amplifier Module
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set thevolume (0-100)
  audio.setVolume(10);

  // Connect to an Internet radio station (select one as desired)
  // audio.connecttohost("www.antenne.de/webradio/antenne.m3u");
  // audio.connecttohost("0n-80s.radionetz.de:8000/0n-70s.mp3");

  // Liferadio Tirol
  //  http://194.232.200.164:8000

  // ö3
  // audio.connecttohost("https://orf-live.ors-shoutcast.at/oe3-q1a.m3u");

  // kronehit
  audio.connecttohost("http://onair.krone.at/kronehit.mp3");
}

void loop()

{
  audio.loop(); 
}

// Audio status functions
void audio_info(const char *info)
{
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info)
{ // id3 metadata
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info)
{ // end of file
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info)
{
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreaminfo(const char *info)
{
  Serial.print("streaminfo  ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info)
{
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info)
{
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info)
{ // duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info)
{ // homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info)
{ // stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
void audio_eof_speech(const char *info)
{
  Serial.print("eof_speech  ");
  Serial.println(info);
}