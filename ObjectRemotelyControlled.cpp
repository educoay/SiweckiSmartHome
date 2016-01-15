#include "ObjectRemotelyControlled.h"

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
}

char* ObjectRemotelyControlled::getRemoteName() {
  return this->name;
}

char* ObjectRemotelyControlled::getTopHierarchyName(char* objectFullRemoteName, char* topHierarchyName) {
  int delimeterIndex = objectFullRemoteName.substring(1).indexOf(LOCATION_DELIMETER);
  if (delimeterIndex >= 0) {
    return objectFullRemoteName.substring(1,delimeterIndex + 1);
  } else {
    return objectFullRemoteName.substring(1);
  } 
}

String ObjectRemotelyControlled::getSublocation(String objectFullRemoteName) {
  int delimeterIndex = objectFullRemoteName.substring(1).indexOf(LOCATION_DELIMETER);
  if (delimeterIndex > 0) {
    return objectFullRemoteName.substring(delimeterIndex + 1);
  } else {
    return "";
  }   
}

void ObjectRemotelyControlled::sendStateUpdate() {
  if (controllerConnector != NULL) {
	  char* objectFullRemoteName = new char[getFullRemoteNameSize() + 1];
	  objectFullRemoteName = getFullRemoteName(objectFullRemoteName);
	  controllerConnector->sendCommand(objectFullRemoteName, createCommand());
	  delete objectFullRemoteName;
	  Serial.println("Update sent.");
  } else {
	  Serial.println("No connector, update skipped");
  }
}

