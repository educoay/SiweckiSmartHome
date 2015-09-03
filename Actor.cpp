#include "RealEstate.h"

RealEstate::RealEstate(String name):RemotlyControlled(name) {
  rooms = 0;
  for(int i = 0; i < REALESTATE_MAX_POINTS; i++){
    roomsTable[i] = NULL;
  } 
}

RealEstate::~RealEstate() {
  for(int i = 0; i < rooms; i++){
    delete roomsTable[i];
    roomsTable[i] = NULL;
  } 
  rooms = 0;
}

void RealEstate::addRoom(Room* room) {
  room->setParent(this);
  roomsTable[rooms] = room;
  rooms++;
}

void RealEstate::initialize() {
  Serial.println("RealEstate init... ");
  for(int i = 0; i < rooms; i++){
    roomsTable[i]->initialize();
  };
}

void RealEstate::verifyControlPoints() {
  for(int i = 0; i < rooms; i++){
    //Serial.println("Room: " + roomsTable[i]->getRemoteName());
    roomsTable[i]->verifyControlPoints();
  }
}

String RealEstate::createCommand() {
  return getRemoteName();
}

void RealEstate::executeCommand(String queue, String command) {
  String estateRemoteName = getNextRemotlyControlled(queue);
  String roomCommand = getSubCommand(queue);
  String roomRemoteName = getNextRemotlyControlled(queue);
  bool find = false;
/*
  Serial.println("Estate: " + estateRemoteName);
  Serial.println("Room: '" + roomRemoteName + "'");
  Serial.println("Room command: " + roomCommand);
  */
  if (estateRemoteName != this->name) {
    Serial.println("Unknown estate name '" + estateRemoteName + "'. Ignored");
  }
  
  for(int i = 0; i < rooms && !find; i++) {
    //Serial.println("Room to check: '" + roomsTable[i]->getRemoteName() + "'");
    if (roomsTable[i]->getRemoteName() == roomRemoteName) {
      roomsTable[i]->executeCommand(getSubCommand(roomCommand));
      find = true;
    }
  }
  //Serial.println("Rooms checked.");
  if (!find) {
    Serial.println("There is no room in estate from command " + estateCommand);
  }
}

