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

String Room::getRemoteName() {
  if (parent != NULL) {
    return parent->getRemoteName() + LOCATION_DELIMETER + this->name;  
  } else {
    return "";
  }
}


String Room::createCommand() {
  return getRemoteName();
}


void Room::executeCommand(String roomCommand) {
  String pointRemoteName = getNextRemotlyControlled(roomCommand);
  String pointAction = getSubCommand(roomCommand);
  bool find = false;
 
  for(int i = 0; i < ROOM_MAX_POINTS && !find; i++) {
    if (pointsTable[i]->getName() == pointRemoteName) {
      pointsTable[i]->executeCommand(pointAction);
      find = true;
    }
  }
  if (!find) {
    Serial.println("There is no point in rooms from command " + roomCommand);
  }
}

