#include "ObjectRemotelyControlled.h"
#include "Const.h"

char* ObjectRemotelyControlled::getFullRemoteName(char* fullRemoteName) {
	if (this->parent != NULL) {
				parent->getFullRemoteName(fullRemoteName);
	}
	strcat(fullRemoteName, LOCATION_DELIMETER);
	strcat(fullRemoteName, this->name);
	return fullRemoteName;
}

int ObjectRemotelyControlled::getFullRemoteNameSize() {
	int parentSize = 0;
	if (parent != NULL) {
		parentSize = parent->getFullRemoteNameSize();
	};
	return parentSize + sizeof(LOCATION_DELIMETER) + strlen(this->name);
}

char* ObjectRemotelyControlled::getRemoteName() {
  return this->name;
}

char* ObjectRemotelyControlled::getTopHierarchyName(const char* objectFullRemoteName, char* topHierarchyName) {
	//char* start = objectFullRemoteName;
	if (objectFullRemoteName[0] == LOCATION_DELIMETER[0]) {
		objectFullRemoteName++;
	}
	char* end = strstr(objectFullRemoteName, LOCATION_DELIMETER);
	if (!end) {
		return NULL;
	}
	return strncpy(topHierarchyName, objectFullRemoteName, end-objectFullRemoteName);
}

char* ObjectRemotelyControlled::getSublocation(const char* objectFullRemoteName) {
	return strstr(objectFullRemoteName++, LOCATION_DELIMETER);
}

void ObjectRemotelyControlled::sendStateUpdate() {
  if (controllerConnector != NULL) {
	  char* objectFullRemoteName = new char[getFullRemoteNameSize() + 1];
	  objectFullRemoteName = getFullRemoteName(objectFullRemoteName);
	  char* command = new char[20];
	  controllerConnector->sendCommand(objectFullRemoteName, createCommand(command));
	  delete objectFullRemoteName;
	  delete command;
	  Serial.println("Update sent.");
  } else {
	  Serial.println("No connector, update skipped");
  }
}

