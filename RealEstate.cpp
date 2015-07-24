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

String RealEstate::getObjectName() {
  return this->name;
}

String RealEstate::createCommand(int state) {
  
}

String RealEstate::createCommand() {
  
}

