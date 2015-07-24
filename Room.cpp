#include "room.h"

Room::Room(String name) {
  this->name = name;
  points = 0;
  for(int i = 0; i < ROOM_MAX_POINTS; i++){
    pointsTable[i] = NULL;
  } 
}

Room::~Room() {
  for(int i = 0; i < ROOM_MAX_POINTS; i++){
    delete pointsTable[i];
    pointsTable[i] = NULL;
  } 
}

void Room::addPoint(Point* point) {
  pointsTable[points] = point;
  pointsTable[points]->setParent(this);
  points++;
}

void Room::initialize() {
  for(int i = 0; pointsTable[i] != NULL; i++){
    pointsTable[i]->initialize();
  }
}

void Room::verifyControlPoints() {  
  for(int i = 0; pointsTable[i] != NULL; i++){
    pointsTable[i]->verifyControlPoint();
  }
}

String Room::getObjectName() {
  return commandParent->getObjectName() + LOCATION_DELIMETER + this->name;  
}

String Room::createCommand(int state) {
  
}

String Room::createCommand() {
  
}

