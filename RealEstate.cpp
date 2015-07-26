#include "RealEstate.h"

RealEstate::RealEstate(String name) {
  this->name = name;
  rooms = 0;
  for(int i = 0; i < REALESTATE_MAX_POINTS; i++){
    roomsTable[i] = NULL;
  } 
}

RealEstate::~RealEstate() {
  for(int i = 0; i < REALESTATE_MAX_POINTS; i++){
    delete roomsTable[i];
  } 
}

void RealEstate::addRoom(Room* room) {
  roomsTable[rooms] = room;
  roomsTable[rooms]->setParent(this);
  rooms++;
}

void RealEstate::initialize() {
  for(int i = 0; roomsTable[i] != NULL; i++){
    roomsTable[i]->initialize();
  }
}

void RealEstate::verifyControlPoints() {
  for(int i = 0; roomsTable[i] != NULL; i++){
    roomsTable[i]->verifyControlPoints();
  }
}

String RealEstate::getRemoteName() {
  return this->name;
}


String RealEstate::createCommand() {
  return getRemoteName();
}

void RealEstate::executeCommand(String estateCommand) {
  String estateRemoteName = getNextRemotlyControlled(estateCommand);
  String roomCommand = getSubCommand(estateCommand);
  String roomRemoteName = getNextRemotlyControlled(roomCommand);
  bool find = false;
  
  if (estateRemoteName != this->name) {
    Serial.println("Unknown estate name '" + estateRemoteName + ". Ignored");
  }
  
  for(int i = 0; i < REALESTATE_MAX_POINTS && !find; i++) {
    if (roomsTable[i]->getName() == roomRemoteName) {
      roomsTable[i]->executeCommand(getSubCommand(roomCommand));
      find = true;
    }
  }
  if (!find) {
    Serial.println("There is no room in estate from command " + estateCommand);
  }
}

