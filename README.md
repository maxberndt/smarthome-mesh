# ESP32 Smarthome Mesh
Based on painlessMesh

## Modules + Pinout
### Bridge Module
Root node, creates json file, bridge between home network/Wifi Network and mesh network.

**Pinout:** -
**Services:**
* Async TCP Webserver: Delivers current sensor values via json, accepts GET requests
* GET REQUESTS: UPPER *(ON/OFF)*: Send Broadcast "O"
