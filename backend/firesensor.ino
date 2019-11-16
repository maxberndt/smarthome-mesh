#include "painlessMesh.h"

#define   MESH_PREFIX     "SmartHomeMesh"
#define   MESH_PASSWORD   "meshit2thelimit"
#define   MESH_PORT       5555
#define   ANALOG A0
#define   SPEAKER 25

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
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

void alarmSound(int c){
  unsigned char i, j ;
  for(int i=0;i<c;i++){
    for (i = 0; i <500; i++){
        digitalWrite (SPEAKER, HIGH) ;// send voice
        delay (1) ;// Delay 1ms
        digitalWrite (SPEAKER, LOW) ;// do not send voice
        delay (1) ;// delay ms
    }
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode (analog, INPUT) ;
  pinMode (speaker, OUTPUT);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
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
  
  if(analogRead(ANALOG) < 100){
    mesh.sendBroadcast("F");
    alarmSound(20);
  }
  
}
