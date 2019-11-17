#include "painlessMesh.h"

#define   MESH_PREFIX     "SmartHomeMesh"
#define   MESH_PASSWORD   "meshit2thelimit"
#define   MESH_PORT       5555
#define   LIGHTSUP        27  //Upper Floor
#define   LIGHTSLOW       25  //Lower Floor

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// Needed for painless library
void receivedCallback(uint32_t from, String &msg) {

  //Lights on
  if(msg[0] == 'O'){
    Serial.printf("Lower Lights on!");
    digitalWrite(LIGHTSLOW, HIGH);
  }

  else if(msg[0] == 'E'){
    Serial.printf("Lower Lights off!");
    digitalWrite(LIGHTSLOW, LOW);
  }
  
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  pinMode(LIGHTSUP, OUTPUT);
  pinMode(LIGHTSLOW, OUTPUT);
  
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
