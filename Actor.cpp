#include "Actor.h"
#include "Const.h"

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
  room->setParent(this);
  roomsTable[rooms] = room;
  rooms++;
}

void Actor::initialize() {
  Serial.println("Actor init... ");
  for(int i = 0; i < rooms; i++){
    roomsTable[i]->initialize();
  };
}

void Actor::verifyControlPoints() {
  for(int i = 0; i < rooms; i++){
    //Serial.println("Room: " + roomsTable[i]->getRemoteName());
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

void Actor::executeCommand(const char* queue, const char* command) {
	//get Actor name form queue /Adr0/Out/Room1/Point1 -> Adr0
	char actorRemoteName[NAME_LIMIT];
	getTopHierarchyName(queue, actorRemoteName);

	//get name of queue which indicates direction
	// /Adr0/Out/Room1/Point1 -> /Out/Room1/Point1
	char* subQueue = getSublocation(queue);
	char direction[NAME_LIMIT];
	// /Out/Room1/Point1 -> Out
	getTopHierarchyName(subQueue, direction);

	char roomSubQueue[NAME_LIMIT];
	// /Out/Room1/Point1 -> /Room1/Point1
	getSublocation(subQueue);
	char roomRemoteName[NAME_LIMIT];
	// /Room1/Point1 -> Room1
	getTopHierarchyName(roomSubQueue, roomRemoteName);

	bool find = false;

/*
  Serial.println("Actor: " + actorRemoteName);
  Serial.println("SubQueue: " + subQueue);
  Serial.println("Direction: " + direction);  
  Serial.println("Room: '" + roomRemoteName + "'");
  Serial.println("Room SubQueue: " + roomSubQueue);
*/
  if (!strcmp(actorRemoteName, this->name)) {
	  Serial.print("Unknown actor name '");
	  Serial.print(actorRemoteName);
	  Serial.println("'. Ignored");
  	  }
  
  for(int i = 0; i < rooms && !find; i++) {
    //Serial.println("Room to check: '" + roomsTable[i]->getRemoteName() + "'");
	  if (strcmp(roomsTable[i]->getRemoteName(), roomRemoteName)) {
		  roomsTable[i]->executeCommand(getSublocation(roomSubQueue), command);
		  find = true;
	  }
  }
  //Serial.println("Rooms checked.");
  if (!find) {
	  Serial.print("There is no room in actor from command ");
	  Serial.print(queue);
	  Serial.print(" ");
	  Serial.println(command);
  }
}

