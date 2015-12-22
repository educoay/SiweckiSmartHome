#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include "Actor.h"
#include "Room.h"
#include "LightPoint.h"

const String ACTOR_NAME = "Ard1";
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
  Serial.print("Queue: ");
  Serial.println(topic);
  Serial.print("Message received: ");
  Serial.println(command);
  actor.executeCommand(topic, command);
  Serial.println("Callback finished.");
}
