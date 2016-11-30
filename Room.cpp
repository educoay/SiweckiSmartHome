#include "Room.h"
#include "GeneralOutputStream.h"

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
  //TODO check if ROOM_MAX_POINTS exceeded.
  if (point == NULL) {
	  return;
  }
  if (points == ROOM_MAX_POINTS) {
	  DiagnosticOutputStream.sendln("Max number points exceeded");
  }
  point->setParent(this);
  pointsTable[points] = point;
  points++;
}

void Room::setControllerConnector(ControllerConnector* _controllerConnector) {
	ObjectRemotelyControlled::setControllerConnector(_controllerConnector);
	for(int i = 0; i < points; i++){
		pointsTable[i]->setControllerConnector(_controllerConnector);
	};
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

void Room::executeCommand(const char* remoteName, const char* command) {
  char pointRemoteName[NAME_LIMIT];
  getTopHierarchyName(remoteName, pointRemoteName);

  bool find = false;

  for(int i = 0; i < points && !find; i++) {
    if (strcmp(pointsTable[i]->getRemoteName(), pointRemoteName) == 0) {
      pointsTable[i]->executeCommand(remoteName, command);
      find = true;
    }
  }
  if (!find) {
	DiagnosticOutputStream.sendln("Error in Room ", this->name, ", points: ", this->points);
	DiagnosticOutputStream.sendln("There is no point ", pointRemoteName, " from command ", remoteName);
  }
}

