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

  for(int i=0;i<c;i++){
    for (int j = 0; j < 500; j++){
        digitalWrite (SPEAKER, HIGH) ;// send voice
        delay (1) ;// Delay 1ms
        digitalWrite (SPEAKER, LOW) ;// do not send voice
        delay (1) ;// delay ms
    }
    delay(200);
    
    for (int j = 0; j < 500; j++){
        digitalWrite (SPEAKER, HIGH) ;// send voice
        delay (2) ;// Delay 1ms
        digitalWrite (SPEAKER, LOW) ;// do not send voice
        delay (2) ;// delay ms
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode (ANALOG, INPUT) ;
  pinMode (SPEAKER, OUTPUT);

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
  
  if(analogRead(ANALOG) < 50){
    mesh.sendBroadcast("F");
    alarmSound(5);
  }
  
}
