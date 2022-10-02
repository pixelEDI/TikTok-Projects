![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white) <img src="https://img.shields.io/badge/-PlattformIO-orange.svg?&amp;style=flat-square&amp" style="max-width: 100%;">



# Seeed Stduio XIAO ESP32C3 MQTT

A quick example to see what is possible with this tiny IoT-Device:  

- Send DHT11 Data via MQTT to Node-Red
- Turn on and turn off a LED via MQTT from Node-Red

## What you need
0) Check platformio.ini and download/build the necessary files with ctrl+alt+b
1) Import flows.json into Node-Red
2) edit src/credentials.h
3) edit mqtt Server Address in src/main.cpp
4) upload Code
5) Have Fun