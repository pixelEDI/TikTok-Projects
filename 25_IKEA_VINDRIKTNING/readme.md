![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

Get the pm2,5 Values from the IKEA VINDRIKTNING Sensor. 

#Hardware
* ESP8266
* IKEA VINDRIKTNING

## General info 

* Note the different TTL of sensor (4.5V) and ESP8266 (3.3V). If you are brave, you can try it without logic level shifter, otherwise use one.
<img src="https://github.com/pixelEDI/TikTok-Projects/blob/c5845b72b9f8f691179f7b9ef47fde411602ca6f/25_IKEA_VINDRIKTNING/logicAnalyzer.png" width="500">
* According to the data sheet (PM10006) and the evaluation from the logic analyzer we get the following response:
 16 0d 02 DF1- DF4 DF5- DF8 DF9- DF12 [CS]
* PM2.5(μg/m3)= DF3*256+DF4. The 5 and 6 byte (index=0) is the pm2.5 value. 

## Wiring: 
RESET from IKEA Sensor to D2 of ESP8266. GND to GND.

You like it? Then I would be very happy if you treat me to a coffee on [ko-fi.com/pixeledi](https://www.ko-fi.com/pixeledi)
