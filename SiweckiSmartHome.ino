#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "RealEstate.h"
#include "Room.h"
#include "LightPoint.h"

const String REALESTATE_NAME = "SiweckiHome";
const String LIVINGROOM_NAME = "LivingRoom";
const String CORRIDOR_NAME = "Corridor";
const int CORRIDOR_BUTTON_PIN = 2;
const int CORRIDOR_OUTPUT_PIN = 3;
const String CEILING_NAME = "Ceiling";
const int CEILING_BUTTON_PIN = 6;
const int CEILING_OUTPUT_PIN = 7;

const int AFTER_CHANGE_DELAY = 1;

RealEstate realEstate = RealEstate(REALESTATE_NAME);
 
void setup() {
  Serial.begin(9600);
  Room *livingRoom = new Room(LIVINGROOM_NAME);  
  LightPoint *ceiling = new LightPoint(CEILING_BUTTON_PIN, CEILING_OUTPUT_PIN, CEILING_NAME);
  LightPoint *corridor = new LightPoint(CORRIDOR_BUTTON_PIN, CORRIDOR_OUTPUT_PIN, CORRIDOR_NAME);

  realEstate.addRoom(livingRoom);
  livingRoom->addPoint(ceiling);
  livingRoom->addPoint(corridor);
  realEstate.initialize();
}
 
void loop() {
  realEstate.verifyControlPoints();
  delay(AFTER_CHANGE_DELAY);
}

 /*

 
void sendMqttState(String state) {
  Serial.print("STATE: ");
  Serial.print(state);

  boolean connected = mqttClient.connected();
  if (!connected) {
     initializeMqtt();
  }
  char ssid[state.length() + 1];        
  state.toCharArray(ssid, state.length() + 1);
  boolean publishState = mqttClient.publish(QUEUE_SERVER, ssid); 
  Serial.print(" published: ");
  Serial.println(publishState);
}

void checkMqtt()
{
  mqttClient.loop();
}

*/

 /*
void executeRemoteCommand(String command) {
  Serial.println(command);

  // Read each command pair 
  int locationDelimeterIndex = command.indexOf(LOCATION_DELIMETER);
  int stateDelimeterIndex = command.indexOf(STATE_DELIMETER);
  String location = command.substring(locationDelimeterIndex);
  String actor = command.substring(locationDelimeterIndex + 1, stateDelimeterIndex);
  String state = command.substring(stateDelimeterIndex + 1, command.length());
  Serial.println(location + ":" + actor + ":" + state);

  if (state == COMMAND_ON) {
      livingRoom.setLightPointOn();
  } else if (state == COMMAND_OFF) {
      livingRoom.setLightPointOff();
  }
}
*/
 

 
