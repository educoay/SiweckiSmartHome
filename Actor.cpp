#include "Actor.h"
#include "Const.h"
#include "GeneralOutputStream.h"

Actor::Actor():ObjectRemotelyControlled() {
  rooms = 0;
  for(int i = 0; i < ACTOR_MAX_ROOMS; i++){
    roomsTable[i] = NULL;
  }
}

Actor::Actor(const char* name):ObjectRemotelyControlled(name) {
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
  //TODO check if ACTOR_MAX_ROOMS exceeded.
  room->setParent(this);
  roomsTable[rooms] = room;
  rooms++;
}

void Actor::initialize() {
  for(int i = 0; i < rooms; i++){
    roomsTable[i]->initialize();
  };
}

void Actor::verifyControlPoints() {
  for(int i = 0; i < rooms; i++){
    //DiagnosticOutputStream.sendln("Room: ", roomsTable[i]->getRemoteName());
    roomsTable[i]->verifyControlPoints();
  }
}

int Actor::getFullRemoteNameSize() {
	return strlen(LOCATION_DELIMETER) + strlen(this->name) + max(strlen(IN_DIRECTION), strlen(OUT_DIRECTION));
}

char* Actor::getFullRemoteName(char* fullRemoteName) {
	if (parent != NULL) {
		return parent->getFullRemoteName(fullRemoteName);
	} else {
		strcat(fullRemoteName, LOCATION_DELIMETER);
		strcat(fullRemoteName, this->name);
		strcat(fullRemoteName, LOCATION_DELIMETER);
		strcat(fullRemoteName, OUT_DIRECTION);
		return fullRemoteName;
	}
}

char* Actor::createCommand(char* command) {
  return command;
}

char* Actor::createCommand(int state, char* command) {
  return command;
}

void Actor::executeCommand(const char* remoteName, const char* command) {
	//get Actor name form queue /Adr0/Out/Room1/Point1 -> Adr0
	char actorRemoteName[NAME_LIMIT];
	getTopHierarchyName(remoteName, actorRemoteName);

	//get name of queue which indicates direction
	// /Adr0/In/Room1/Point1 -> /In/Room1/Point1
	char* subQueue = getSublocation(remoteName);
	char direction[NAME_LIMIT];
	// /In/Room1/Point1 -> In
	getTopHierarchyName(subQueue, direction);

	//get the name of Room, /In/Room1/Point1 -> /Room1/Point1
	char* roomSubQueue = getSublocation(subQueue);
	char roomRemoteName[NAME_LIMIT];
	// /Room1/Point1 -> Room1
	getTopHierarchyName(roomSubQueue, roomRemoteName);

	bool find = false;

/*
  DiagnosticOutputStream.sendln("Actor: ", actorRemoteName);
  DiagnosticOutputStream.sendln("SubQueue: ", subQueue);
  DiagnosticOutputStream.sendln("Direction: ", direction);
  DiagnosticOutputStream.sendln("Room: ", roomRemoteName);
  DiagnosticOutputStream.sendln("Room SubQueue: ", roomSubQueue);
*/

  if (strcmp(actorRemoteName, this->name) != 0) {
	  DiagnosticOutputStream.sendln("Unknown act name ", actorRemoteName, ". Ignored");
	  return;
  }
  
  for(int i = 0; i < rooms && !find; i++) {
	  if (strcmp(roomsTable[i]->getRemoteName(), roomRemoteName) == 0) {
		  roomsTable[i]->executeCommand(getSublocation(roomSubQueue), command);
		  find = true;
	  }
  }
  //DiagnosticOutputStream.sendln("Rooms checked");
  if (!find) {
	  DiagnosticOutputStream.sendln("No room in act from comm ", remoteName, " ", command);
  }
}

