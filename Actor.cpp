#include "Actor.h"

Actor::Actor(String name):RemotlyControlled(name) {
  rooms = 0;
  for(int i = 0; i < ACTOR_MAX_ROOMS; i++){
    roomsTable[i] = NULL;
  } 
}

Actor::~Actor() {
  for(int i = 0; i < rooms; i++){
    delete roomsTable[i];
    roomsTable[i] = NULL;
  } 
  rooms = 0;
}

void Actor::addRoom(Room* room) {
  room->setParent(this);
  roomsTable[rooms] = room;
  rooms++;
}

void Actor::initialize() {
  Serial.println("Actor init... ");
  for(int i = 0; i < rooms; i++){
    roomsTable[i]->initialize();
  };
}

void Actor::verifyControlPoints() {
  for(int i = 0; i < rooms; i++){
    //Serial.println("Room: " + roomsTable[i]->getRemoteName());
    roomsTable[i]->verifyControlPoints();
  }
}


String Actor::getFullRemoteName() {
  if (parent != NULL) {
    return parent->getFullRemoteName() + LOCATION_DELIMETER + this->name;  
  } else {
    return LOCATION_DELIMETER + this->name + LOCATION_DELIMETER + OUT_DIRECTION;
  }
}

String Actor::createQueue() {
  return getRemoteName();
}

String Actor::createCommand() {
  return "";
}

void Actor::executeCommand(String queue, String command) {
  String actorRemoteName = getNextRemotlyControlled(queue);
  String subQueue = getSubRemotlyControlled(queue);
  String direction = getNextRemotlyControlled(subQueue);
  String roomSubQueue = getSubRemotlyControlled(subQueue);
  String roomRemoteName = getNextRemotlyControlled(roomSubQueue);
  bool find = false;
/*
  Serial.println("Actor: " + actorRemoteName);
  Serial.println("SubQueue: " + subQueue);
  Serial.println("Direction: " + direction);  
  Serial.println("Room: '" + roomRemoteName + "'");
  Serial.println("Room SubQueue: " + roomSubQueue);
*/
  if (actorRemoteName != this->name) {
    Serial.println("Unknown actor name '" + actorRemoteName + "'. Ignored");
  }
  
  for(int i = 0; i < rooms && !find; i++) {
    //Serial.println("Room to check: '" + roomsTable[i]->getRemoteName() + "'");
    if (roomsTable[i]->getRemoteName() == roomRemoteName) {
      roomsTable[i]->executeCommand(getSubRemotlyControlled(roomSubQueue), command);
      find = true;
    }
  }
  //Serial.println("Rooms checked.");
  if (!find) {
    Serial.println("There is no room in actor from command " + queue + " " + command);
  }
}

