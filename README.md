# SmartFireAlarm

Note: Our project's real cloud side was coded with IBM bluemix but right now the bluemix app is down and we couldn't solve the problem, we had a Thingspeak code as a back up so we had to go with it.

# Description of the project

### Problem

Fire alarms detect the fire after it started, after that point fire damages properties and human lives. Preventing fire from happening is the real challenge and since most of the causes leading to the fire can be monitored we wanted to detect the possibility of fire.

### Solution

We used smoke sensor for detecting the fire situation and gas sensor, temperature, humidity sensor for detecting possibility of fire and warn people about the situation and the cause of the fire possibility and if fire detected the sound the alarms.

# Team Members

Yusufcan Manav

Ahmet Mert Yavuz

Buğra Taşdan

# Hardware Setup

We used Arduino as our main board and ESP8266 for connectivity. DHT11 is connected to the D7 of Arduino. DS18B20 connected to the D10 of Arduino. MQ2 connected to the A1 and MQ4 is connected to the A2 of the Arduino. Buzzer is connected D12.

For using DS18B20 we used DallasTemperature library from https://github.com/milesburton/Arduino-Temperature-Control-Library

# Flow of Data

- Sensor taken with arduino, if smoke sensor value exceeded threshold sound the alarm.
- Collected sensor data send to the Thingspeak
- Periodically analysis algorithm work on the cloud and check if there is a situation that can lead to fire
- Also smoke sensor values checked on insertion for detecting fire situation in cloud
- If there is an anomality we send email to the users using IFTTT for warning


