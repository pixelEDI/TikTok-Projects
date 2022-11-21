# General info

## TimeTagger
We use timetagger.io with docker. Check out original project description:
https://timetagger.app/articles/selfhost2/

TimeTagger has a simple WebAPI: https://timetagger.readthedocs.io/en/latest/webapi/   
You need a Auth-Token from for HTTP-Request.

## Node-RED
check out the flows.json for the Node-RED Flow.

* Install node-red-contrib-filesystem in Node-Red
* According to the WEB Api from TimeTagger the Client has to deal with the start of a task. 
* The CheckIn/start of a Task will be safed in a TXT-File.
    * if no File exists, a JSON according to the specs from timetagger will be safed.
    * If a File exists, a HTTP PUT will be send to the API and the Record will be insert into TimeTagger. After that - the TXT File will be deleted.


## Hardware
- For this project we used an ESP32 Mini.
- RFID Kit
- 2x LEDs

Fritzing will be added soon

You like it? Then I would be very happy if you treat me to a coffee on [ko-fi.com/pixeledi](https://www.ko-fi.com/pixeledi)
