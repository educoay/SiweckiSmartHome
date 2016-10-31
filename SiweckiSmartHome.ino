#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "Actor.h"
#include "Room.h"
#include "LightPoint.h"
#include "Configuration.h"
#include "GeneralOutputStream.h"
#include "ConfigurationReader.h"

const char* ACTOR_NAME = "Ard1";
const char* LIVINGROOM_NAME = "LivingRoom";
const char* CORRIDOR_NAME = "Corridor";
const int CORRIDOR_BUTTON_PIN = 2;
const int CORRIDOR_OUTPUT_PIN = 3;
const char* CEILING_NAME = "Ceiling";
const int CEILING_BUTTON_PIN = 6;
const int CEILING_OUTPUT_PIN = 7;

byte mqttServerIP[4] = {192, 168, 1, 190};
int mqttServerPort = 1883;

const int AFTER_CHANGE_DELAY = 100;

Configuration config;

Actor actor = Actor(ACTOR_NAME);
ControllerConnector controllerConnector = ControllerConnector();

EthernetClient ethClient;
PubSubClient mqttClient = PubSubClient(mqttServerIP, mqttServerPort, callback, ethClient);

LightPoint *ceiling = NULL;
LightPoint *corridor = NULL;
int i = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  char* command = (char*)payload;
  DiagnosticOutputStream.sendln("Queue: ", topic, "Msg rcv: ", command);
  actor.executeCommand(topic, command);
  DiagnosticOutputStream.sendln("Callbck fin");
}
 
void setup() {

  Serial.begin(9600);
  DiagnosticOutputStream.setSendToSerial(config.isDebug);
  DiagnosticOutputStream.sendln("Setup begin");

  ConfigurationReader configurationReader;
  if (!configurationReader.setConfiguraionFromFile(&actor, &config)) {
	  return;
  }

  Ethernet.begin(config.mac);
  controllerConnector.setMqttClient(&mqttClient);
  controllerConnector.initialize(ACTOR_NAME);
  Room *livingRoom = new Room(LIVINGROOM_NAME);
  ceiling = new LightPoint(CEILING_BUTTON_PIN, CEILING_OUTPUT_PIN, CEILING_NAME);
  corridor = new LightPoint(CORRIDOR_BUTTON_PIN, CORRIDOR_OUTPUT_PIN, CORRIDOR_NAME);
  //Serial.println("Assign connectivity...");
  ceiling->setControllerConnector(&controllerConnector);
  corridor->setControllerConnector(&controllerConnector);
  //Serial.println("Data structure created.");
  actor.addRoom(livingRoom);
  //Serial.println("Room addded.");
  livingRoom->addPoint(ceiling);
  livingRoom->addPoint(corridor);
  if (config.isDebug) {
	  char* ceilingFullRemoteName = new char[ceiling->getFullRemoteNameSize()];
	  ceiling->getFullRemoteName(ceilingFullRemoteName);
	  DiagnosticOutputStream.sendln("ceiling: ", ceilingFullRemoteName);
	  delete ceilingFullRemoteName;

	  char *corridorFullRemoteName = new char[corridor->getFullRemoteNameSize()];
	  corridor->getFullRemoteName(corridorFullRemoteName);
	  DiagnosticOutputStream.sendln("corridor: ", corridorFullRemoteName);
	  delete corridorFullRemoteName;
  }

  DiagnosticOutputStream.sendln("Act init");
  actor.initialize();
  DiagnosticOutputStream.sendln("Init done");
}
 
void loop() {
	//Serial.print("Loop... "); Serial.println(i++);
	actor.verifyControlPoints();
	mqttClient.loop();
	delay(AFTER_CHANGE_DELAY);
}


 

 
