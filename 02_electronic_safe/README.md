# General info

We have built an electronic safe that can be opened with an RFID tag. As soon as the safe is unlocked, you receive a notification via MQTT to your email address. 
If you try to open the safe with an incorrect RFID tag, a red LED lights up. 

## Hardware
- The ESP32 is our microcontroller of choice for this homemade electronic safe. 
- For the locking mechanism, we added an MG996R servo motor controlled by an RFID module.
- We added a 220 Ω resistor for the red LED and a WS2812B LED strip for the interior lighting.
- We also added a voltage transformer, so we can power the safe with a regular power supply.

<img src="https://github.com/pixelEDI/TikTok-Projects/blob/323304f11b6fbd901b09f2f06fc43bd67466c3c7/02_electronic_safe/10tresor_Steckplatine.png" width="300">

## Node-Red
- Install in Node-Red the "node-red-node-email" 
- Import flow: node-red-flow.json


You like it? Then I would be very happy if you treat me to a coffee on [ko-fi.com/pixeledi](https://www.ko-fi.com/pixeledi)

