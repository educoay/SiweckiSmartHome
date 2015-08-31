#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "RealEstate.h"
#include "Room.h"
#include "LightPoint.h"

const String REALESTATE_NAME = "SSH";
const String LIVINGROOM_NAME = "LivingRoom";
const String CORRIDOR_NAME = "Corridor";
const int CORRIDOR_BUTTON_PIN = 2;
const int CORRIDOR_OUTPUT_PIN = 3;
const String CEILING_NAME = "Ceiling";
const int CEILING_BUTTON_PIN = 6;
const int CEILING_OUTPUT_PIN = 7;

byte mac[6] = {0x00, 0x12, 0xFB, 0x95, 0x59, 0xCF};

byte mqttServerIP[4] = {192, 168, 1, 190};
int mqttServerPort = 1883;

const int AFTER_CHANGE_DELAY = 100;

RealEstate realEstate = RealEstate(REALESTATE_NAME);
ControllerConnector controllerConnector = ControllerConnector();

EthernetClient ethClient;
PubSubClient mqttClient = PubSubClient(mqttServerIP, mqttServerPort, callback, ethClient);

LightPoint *ceiling = NULL;
LightPoint *corridor = NULL;
int i = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  char* strPayload = (char*)payload;
  Serial.print("Message received: ");
  Serial.println(strPayload);
  realEstate.executeCommand(strPayload);
  Serial.println("Callback finished.");
}
 
void setup() {
  Serial.begin(9600);
  Serial.println("Setup begin...");
  Ethernet.begin(mac);
  controllerConnector.setMqttClient(&mqttClient);
  controllerConnector.initialize();
  Room *livingRoom = new Room(LIVINGROOM_NAME);
  ceiling = new LightPoint(CEILING_BUTTON_PIN, CEILING_OUTPUT_PIN, CEILING_NAME);
  corridor = new LightPoint(CORRIDOR_BUTTON_PIN, CORRIDOR_OUTPUT_PIN, CORRIDOR_NAME);
  //Serial.println("Assign connectivity...");
  ceiling->setControllerConnector(&controllerConnector);
  corridor->setControllerConnector(&controllerConnector);
  //Serial.println("Data structure created.");
  realEstate.addRoom(livingRoom);
  //Serial.println("Room addded.");
  livingRoom->addPoint(ceiling);
  livingRoom->addPoint(corridor);
  Serial.println("ceiling: " + ceiling->getFullRemoteName());
  Serial.println("corridor: " + corridor->getFullRemoteName());
  realEstate.initialize();
  Serial.println("Init done.");
}
 
void loop() {
  //Serial.print("Loop... "); Serial.println(i++);
  realEstate.verifyControlPoints();
  mqttClient.loop();
  delay(AFTER_CHANGE_DELAY);
}


 

 
