#include "ObjectRemotelyControlled.h"
#include "Const.h"
#include "GeneralOutputStream.h"

ObjectRemotelyControlled::ObjectRemotelyControlled() {
	this->name = NULL;
}

ObjectRemotelyControlled::ObjectRemotelyControlled(const char* name) {
	this->name = strdup(name);
}

void ObjectRemotelyControlled::setName(char* name) {
	delete this->name;
	this->name = strdup(name);
}

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
	if (objectFullRemoteName[0] == LOCATION_DELIMETER[0]) {
		objectFullRemoteName++;
	}
	char* end = strstr(objectFullRemoteName, LOCATION_DELIMETER);
	if (end == NULL) {
		return strcpy(topHierarchyName, objectFullRemoteName);
	}
	strncpy(topHierarchyName, objectFullRemoteName, end-objectFullRemoteName);
	topHierarchyName[end-objectFullRemoteName] = '\0';
	return topHierarchyName;
}

char* ObjectRemotelyControlled::getSublocation(const char* objectFullRemoteName) {
	return strstr(++objectFullRemoteName, LOCATION_DELIMETER);
}

void ObjectRemotelyControlled::sendStateUpdate() {
  if (controllerConnector != NULL) {
	  char* objectFullRemoteName = new char[getFullRemoteNameSize() + 1];
	  objectFullRemoteName = getFullRemoteName(objectFullRemoteName);
		char* command = new char[MAX_COMMAND_LENGTH];
	  controllerConnector->sendCommand(objectFullRemoteName, createCommand(command));
	  delete objectFullRemoteName;
	  delete command;
	  DiagnosticOutputStream.sendln("Update sent");
  } else {
	  DiagnosticOutputStream.sendln("No connector, update skipped");
  }
}

