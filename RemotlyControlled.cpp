#include "RemotlyControlled.h"

String RemotlyControlled::getNextRemotlyControlled(String command) {
  int locationDelimeterIndex = command.indexOf(LOCATION_DELIMETER);
  int stateDelimeterIndex = 0;
  if (locationDelimeterIndex > 0) {
    return command.substring(0,locationDelimeterIndex);
  } else {
    stateDelimeterIndex = command.indexOf(STATE_DELIMETER);
    if (stateDelimeterIndex > 0) {
      return command.substring(0, stateDelimeterIndex);
    } else {
      return "";
    }
  } 
}

String RemotlyControlled::getSubCommand(String command) {
  int locationDelimeterIndex = command.indexOf(LOCATION_DELIMETER);
  int stateDelimeterIndex = 0;
  if (locationDelimeterIndex > 0) {
    return command.substring(locationDelimeterIndex + 1);
  } else {
    stateDelimeterIndex = command.indexOf(STATE_DELIMETER);
    if (stateDelimeterIndex > 0) {
      return command.substring(stateDelimeterIndex + 1);
    } else {
      return "";
    }
  }   
}

String RemotlyControlled::sendStateUpdate() {
  if (controllerConnector != NULL) {
    controllerConnector->sendCommand(createCommand());
  }
}

