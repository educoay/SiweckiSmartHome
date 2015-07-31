#include "RealEstate.h"

RealEstate::RealEstate(String name):RemotlyControlled(name) {
  //this->name = name;
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
  Serial.println("RealEstate initialization... ");
  for(int i = 0; i < rooms; i++){
    Serial.print("Init Room ");
    Serial.println(i);
    roomsTable[i]->initialize();
  }
  Serial.println("RealEstate initialization done.");
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

void RealEstate::executeCommand(String estateCommand) {
  Serial.println("Cmd: " + estateCommand);
  /*
  String estateRemoteName = getNextRemotlyControlled(estateCommand);
  String roomCommand = getSubCommand(estateCommand);
  String roomRemoteName = getNextRemotlyControlled(roomCommand);
  bool find = false;
  
  if (estateRemoteName != this->name) {
    Serial.println("Unknown estate name '" + estateRemoteName + ". Ignored");
  }
  
  for(int i = 0; i < rooms && !find; i++) {
    if (roomsTable[i]->getRemoteName() == roomRemoteName) {
      roomsTable[i]->executeCommand(getSubCommand(roomCommand));
      find = true;
    }
  }
  if (!find) {
    Serial.println("There is no room in estate from command " + estateCommand);
  }
  */
}

