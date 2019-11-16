#include "IPAddress.h"
#include "painlessMesh.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define   MESH_PREFIX     "SmartHomeMesh"
#define   MESH_PASSWORD   "meshit2thelimit"
#define   MESH_PORT       5555

#define   STATION_SSID     "OnePlus 6T"
#define   STATION_PASSWORD "" //Insert

#define HOSTNAME "SMARTHOME"

// Prototype
void receivedCallback( const uint32_t &from, const String &msg );
IPAddress getlocalIP();

painlessMesh  mesh;
AsyncWebServer server(80);
IPAddress myIP(0,0,0,0);
IPAddress myAPIP(0,0,0,0);

float PV_output = 0;
float temp = 0;
bool lights_groundFloor = false;
bool lights_upperFloor = false;
bool heating = false;
bool fireAlarm = false;

void setup() {
  Serial.begin(115200);

  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  // Channel set to 6. Make sure to use the same channel for your mesh and for you other
  // network (STATION_SSID)
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 11);
  mesh.onReceive(&receivedCallback);

  mesh.stationManual(STATION_SSID, STATION_PASSWORD);
  mesh.setHostname(HOSTNAME);

  // Bridge node, should (in most cases) be a root node. See [the wiki](https://gitlab.com/painlessMesh/painlessMesh/wikis/Possible-challenges-in-mesh-formation) for some background
  mesh.setRoot(true);
  // This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes
  mesh.setContainsRoot(true);

  myAPIP = IPAddress(mesh.getAPIP());
  Serial.println("My AP IP is " + myAPIP.toString());

  //Async webserver
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/json", 
    "{ \n    \"PV_output\": " + String(PV_output) + ",\n    " + 
    "\"temp\": " + String(temp) + ",\n    " + 
    "\"lights_groundFloor\": " + String(lights_groundFloor) + ",\n    " + 
    "\"lights_upperFloor\": " + String(lights_upperFloor) + ",\n    " + 
    "\"heating\": " + String(heating) + ",\n    " + 
    "\"fireAlarm\": " + String(fireAlarm) + "\n" +
    " }"

    );
    if (request->hasArg("UPPER")){
      Serial.println(request->arg("UPPER"));
      
      //String msg = request->arg("BROADCAST");
      if(request->arg("UPPER") == "ON"){
        mesh.sendBroadcast("O");
        lights_upperFloor = true;
        Serial.println("Sent request to activate lights.");
      }

      if(request->arg("UPPER") == "OFF"){
        mesh.sendBroadcast("E");
        lights_upperFloor = false;
        Serial.println("Sent request to deactivate lights.");
      }
      
    }
  });
  server.begin();

}

void loop() {
  mesh.update();
  if(myIP != getlocalIP()){
    myIP = getlocalIP();
    Serial.println("My IP is " + myIP.toString());
  }
}

void receivedCallback( const uint32_t &from, const String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
  if(msg[0] == 'T'){
    temp = msg.substring(1).toFloat();
    Serial.printf("Temp Updateted to %f", temp);
  }  
  
}

IPAddress getlocalIP() {
  return IPAddress(mesh.getStationIP());
}
