#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "Actor.h"
#include "Room.h"
#include "LightPoint.h"
#include "Configuration.h"
#include "GeneralOutputStream.h"
#include "ConfigurationReader.h"

byte mqttServerIP[4] = {192, 168, 1, 190};
int mqttServerPort = 1883;

const int AFTER_CHANGE_DELAY = 100;

Configuration config;

Actor actor = Actor();
ControllerConnector controllerConnector = ControllerConnector();

EthernetClient ethClient;
PubSubClient mqttClient = PubSubClient(mqttServerIP, mqttServerPort, callback, ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  char* command = (char*)payload;
  DiagnosticOutputStream.sendln("Queue: ", topic, " Msg rcv: ", command);
  actor.executeCommand(topic, command);
  //DiagnosticOutputStream.sendln("Callbck fin");
}
 
void setup() {

  Serial.begin(9600);
  DiagnosticOutputStream.setSendToSerial(config.isDebug);
  DiagnosticOutputStream.sendln("Setup begin");

  ConfigurationReader configurationReader;
  if (!configurationReader.readConfigurationFromFile(&actor, &config)) {
	  DiagnosticOutputStream.sendln("Setup exit");
	  return;
  }

  Ethernet.begin(config.mac);
  controllerConnector.setMqttClient(&mqttClient);
  controllerConnector.initialize(config.instanceName);

  DiagnosticOutputStream.sendln("Act init");
  actor.setName(config.instanceName);
  actor.initialize();
  DiagnosticOutputStream.sendln("Init done");
}
 
void loop() {
	actor.verifyControlPoints();
	mqttClient.loop();
	delay(AFTER_CHANGE_DELAY);
}


 

 
