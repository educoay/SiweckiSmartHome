#include "Room.h"

Room::Room(const char* name):ObjectRemotelyControlled(name) {
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

char* Room::createCommand(char* command) {
  return command;
}

char* Room::createCommand(int state, char* command) {
  return command;
}

void Room::executeCommand(const char* objectFullRemoteName, const char* command) {
  char pointRemoteName[NAME_LIMIT];
  getTopHierarchyName(objectFullRemoteName, pointRemoteName);
  bool find = false;

  for(int i = 0; i < points && !find; i++) {
    if (pointsTable[i]->getRemoteName() == pointRemoteName) {
      pointsTable[i]->executeCommand(objectFullRemoteName, command);
      find = true;
    }
  }
  if (!find) {
    Serial.print("There is no point '");
    Serial.print(pointRemoteName);
    Serial.print("' in room '");
    Serial.print(getRemoteName());
    Serial.print("' from command ");
    Serial.println(objectFullRemoteName);
  }
}

