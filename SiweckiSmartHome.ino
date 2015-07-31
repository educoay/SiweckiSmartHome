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

const int AFTER_CHANGE_DELAY = 100;

RealEstate realEstate = RealEstate(REALESTATE_NAME);
ControllerConnector controllerConnector = ControllerConnector();
 
void setup() {
  Serial.begin(9600);
  Serial.println("Initialization begin...");
  Room *livingRoom = new Room(LIVINGROOM_NAME);
  LightPoint *ceiling = new LightPoint(CEILING_BUTTON_PIN, CEILING_OUTPUT_PIN, CEILING_NAME); //, &controllerConnector);
  LightPoint *corridor = new LightPoint(CORRIDOR_BUTTON_PIN, CORRIDOR_OUTPUT_PIN, CORRIDOR_NAME); //, &controllerConnector);
  Serial.println("Data structure created.");
  realEstate.addRoom(livingRoom);
  livingRoom->addPoint(ceiling);
  Serial.println("ceiling: " + ceiling->getRemoteName());
  livingRoom->addPoint(corridor);
  Serial.println("corridor: " + corridor->getRemoteName());
  Serial.println("Data structure assigned.");
  realEstate.initialize();
  controllerConnector.initialize();
  Serial.println("Initialization done.");
}
 
void loop() {
  //Serial.println("Loop...");
  realEstate.verifyControlPoints();
  //controllerConnector.checkOutstandingMessages();
  delay(AFTER_CHANGE_DELAY);
}


 

 
