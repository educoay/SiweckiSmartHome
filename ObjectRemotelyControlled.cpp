#include "ObjectRemotelyControlled.h"

String ObjectRemotelyControlled::getFullRemoteName() {
  if (parent != NULL) {
    return parent->getFullRemoteName() + LOCATION_DELIMETER + this->name;  
  } else {
    return LOCATION_DELIMETER + this->name;
  }
}

String ObjectRemotelyControlled::getRemoteName() {
  return this->name;
}

String ObjectRemotelyControlled::getNextRemotlyControlled(String queue) {
  int locationDelimeterIndex = queue.substring(1).indexOf(LOCATION_DELIMETER);
  if (locationDelimeterIndex >= 0) {
    return queue.substring(1,locationDelimeterIndex + 1);
  } else {
    return queue.substring(1);
  } 
}

String ObjectRemotelyControlled::getSubRemotlyControlled(String queue) {
  int locationDelimeterIndex = queue.substring(1).indexOf(LOCATION_DELIMETER);
  if (locationDelimeterIndex > 0) {
    return queue.substring(locationDelimeterIndex + 1);
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

