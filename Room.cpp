#include "Room.h"

Room::Room(String name):RemotlyControlled(name) {
  //this->name = name;
  points = 0;
  for(int i = 0; i < ROOM_MAX_POINTS; i++){
    pointsTable[i] = NULL;
  } 
}

Room::~Room() {
  for(int i = 0; i < points; i++){
    delete pointsTable[i];
    pointsTable[i] = NULL;
  }
  points = 0;
}

void Room::addPoint(Point* point) {
  point->setParent(this);
  pointsTable[points] = point;
  points++;
}

void Room::initialize() {
  for(int i = 0; i < points; i++) {
    pointsTable[i]->initialize();
  }
}

void Room::verifyControlPoints() {  
  for(int i = 0; i < points; i++){
    pointsTable[i]->verifyControlPoint();
  }
}

String Room::createCommand() {
  return getRemoteName();
}

String Room::createQueue() {
  return getRemoteName();
}

void Room::executeCommand(String queue, String command) {
  String pointRemoteName = getNextRemotlyControlled(queue);
  bool find = false;

  for(int i = 0; i < points && !find; i++) {
    if (pointsTable[i]->getRemoteName() == pointRemoteName) {
      pointsTable[i]->executeCommand(queue, command);
      find = true;
    }
  }
  if (!find) {
    Serial.println("There is no point '" + pointRemoteName  + "' in room '" + getRemoteName() + "' from command " + queue);
  }
}

