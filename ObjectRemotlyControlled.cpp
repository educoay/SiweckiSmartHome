#include "ObjectRemotlyControlled.h"

String ObjectRemotlyControlled::getFullRemoteName() {
  if (parent != NULL) {
    return parent->getFullRemoteName() + LOCATION_DELIMETER + this->name;  
  } else {
    return LOCATION_DELIMETER + this->name;
  }
}

String ObjectRemotlyControlled::getRemoteName() {
  return this->name;
}

String ObjectRemotlyControlled::getNextRemotlyControlled(String queue) {
  int locationDelimeterIndex = queue.substring(1).indexOf(LOCATION_DELIMETER);
  if (locationDelimeterIndex >= 0) {
    return queue.substring(1,locationDelimeterIndex + 1);
  } else {
    return queue.substring(1);
  } 
}

String ObjectRemotlyControlled::getSubRemotlyControlled(String queue) {
  int locationDelimeterIndex = queue.substring(1).indexOf(LOCATION_DELIMETER);
  if (locationDelimeterIndex > 0) {
    return queue.substring(locationDelimeterIndex + 1);
  } else {
    return "";
  }   
}

void ObjectRemotlyControlled::sendStateUpdate() {
  if (controllerConnector != NULL) {
    controllerConnector->sendCommand(getFullRemoteName(), createCommand());
    Serial.println("Update sent.");
  } else {
    Serial.println("No connector, update skipped");
  }
}

