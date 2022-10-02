<img src="https://img.shields.io/badge/-PlattformIO-orange.svg?&amp;style=flat-square&amp" style="max-width: 100%;"> <img src="https://img.shields.io/badge/-seeed%20studio-green.svg?&amp;style=flat-square&amp" style="max-width: 100%;"> 


# Seeed Studio XIAO ESP32C3 MQTT

A quick example to see what is possible with this tiny IoT-Device:  

<img src="https://github.com/pixelEDI/TikTok-Projects/blob/main/8_MQTT_seedStudioXIAO/ESPXIAO_Steckplatinebreakout.png" width="300">

- Send DHT11 Data via MQTT to Node-Red
- Turn on and turn off a LED via MQTT from Node-Red

<img src="https://github.com/pixelEDI/TikTok-Projects/blob/main/8_MQTT_seedStudioXIAO/nodered-flows.jpg" width="600">

## What you need
0) Check platformio.ini and download/build the necessary files with ctrl+alt+b
1) Import flows.json into Node-Red
2) edit src/credentials.h
3) edit mqtt Server Address in src/main.cpp
4) upload Code
5) Have Fun
