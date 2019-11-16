# ESP32 Smarthome Mesh
Based on painlessMesh

## Modules + Pinout

### Bridge Module
Root node, creates json file, bridge between home network/Wifi Network and mesh network.

#### Pinout: 
* No Pins used

#### Services:
* Async TCP Webserver: Delivers current sensor values via json, accepts GET requests
* TEMP Update: **Broadcast "TXX.XX"**

#### POSSIBLE GET REQUESTS:

Example Reqeust: 192.168.0.50?LOWER=ON

* LOWER *(ON)*:  **Broadcasts "O"**, Lower Floor Lights
* LOWER *(OFF)*:  **Broadcast "E"**, Lower Floor Lights

### Temp-Module
To Do/Currently not working

### Flame Sensor Module
Detects infrared light with a wavelength ranging from 700nm to 1000nm (emitted by fire). Alarm sound and **Broadcast "F"** if fire detected.

#### Pinout
* A0/D36: Desc: Analog Input for Sensor
* D25: Desc: Speaker

### Lights/Relais Module
Switches Lights on/off. 

#### Pinout
* D27: Desc: Lights upper floor **TODO**
* D25: Desc: Lights lower floor **(on if broadcast msg = O, off if broadcast msg = E)**#
