#include "ObjectRemotelyControlled.h"

String ObjectRemotelyControlled::getFullRemoteName() {
	if (this->parent != NULL) {
		return parent->getFullRemoteName() + LOCATION_DELIMETER + this->getRemoteName();
	}
	return LOCATION_DELIMETER + this->getRemoteName();
}

String ObjectRemotelyControlled::getRemoteName() {
  return this->name;
}

String ObjectRemotelyControlled::getTopHierarchyName(String objectFullRemoteName) {
	int locationDelimeterIndex = objectFullRemoteName.substring(1).indexOf(LOCATION_DELIMETER);
	if (locationDelimeterIndex >= 0) {
		return objectFullRemoteName.substring(1,locationDelimeterIndex + 1);
	} else {
		return objectFullRemoteName.substring(1);
	}
}

String ObjectRemotelyControlled::getSublocation(String objectFullRemoteName) {
	int locationDelimeterIndex = objectFullRemoteName.substring(1).indexOf(LOCATION_DELIMETER);
	if (locationDelimeterIndex > 0) {
	  return objectFullRemoteName.substring(locationDelimeterIndex + 1);
	} else {
		return "";
	}
}

void ObjectRemotelyControlled::sendStateUpdate() {
	   if (controllerConnector != NULL) {
	      controllerConnector->sendCommand(getFullRemoteName(), createCommand());
	      Serial.println("Update sent.");
	   } else {
	     Serial.println("No connector, update skipped");
	   }
}

