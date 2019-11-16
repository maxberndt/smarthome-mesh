# ESP32 Smarthome Mesh
Based on painlessMesh

## Modules + Pinout

### Bridge Module
Root node, creates json file, bridge between home network/Wifi Network and mesh network.

#### Pinout: 
* -

#### Services:
* Async TCP Webserver: Delivers current sensor values via json, accepts GET requests
* TEMP Update: **Broadcast "TXX.XX"**
* GET REQUESTS: UPPER *(ON/OFF)*: Send **Broadcast "O"**

### Temp-Module
To Do/Currently not working

### Flame Sensor Module
Detects infrared light with a wavelength ranging from 700nm to 1000nm (emitted by fire). Alarm sound and **Broadcast "F"** if fire detected.

#### Pinout
* ESP32: A0/D36, Desc: Analog Input for Sensor
* ESP32: D25, Desc: Speaker
