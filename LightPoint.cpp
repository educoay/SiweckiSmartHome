#include "LightPoint.h"
#include "Const.h"
#include "GeneralOutputStream.h"

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, const char* name):Point(name) {
	this->controlButtonPin = controlButtonPin;
	this->controlOutputPin = controlOutputPin;
}

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, const char* name, ControllerConnector *controllerConnector):Point(name) {
  LightPoint(controlButtonPin, controlOutputPin, name);
  this->setControllerConnector(controllerConnector);
}

LightPoint::~LightPoint() {
}


void LightPoint::initialize() {
    pinMode(this->controlButtonPin, INPUT);
    pinMode(this->controlOutputPin, OUTPUT);
}

boolean LightPoint::isControlButtonPressed() {
  int buttonNow =  digitalRead(this->controlButtonPin);  
  if (buttonNow != this->buttonPreviousState) {
    this->buttonPreviousState = buttonNow;
    if(buttonNow == HIGH) {
        //Serial.println(this->getFullRemoteName() + " button pressed");
        return true;
    };
  };
  return false;
}

boolean LightPoint::isLightPointOn() {
  return this->lightPointState == HIGH;
}

void LightPoint::setLightPointOn() {
  setLightPointState(HIGH);
}

void LightPoint::setLightPointOff() {
  setLightPointState(LOW);
}
 
void LightPoint::setLightPointState(int state) {
    digitalWrite(this->controlOutputPin, state);
    this->lightPointState = state;
}

void LightPoint::verifyControlPoint() {
  if (isControlButtonPressed()) {
    if (isLightPointOn()) {
      setLightPointOff();
    } else {
      setLightPointOn();
    }
    sendStateUpdate();
  }
}

char* LightPoint::createCommand(int state, char* command) {
	if (state == LOW) {
		strcpy(command, COMMAND_OFF);
	} else {
		strcpy(command, COMMAND_ON);
	}
	return command;
}

char* LightPoint::createCommand(char* command) {
  return createCommand(this->lightPointState, command);
}

void LightPoint::executeCommand(const char* objectFullRemoteName, const char* command) {
  if (strcmp(command, COMMAND_ON) == 0) {
      setLightPointOn();
  } else if (strcmp(command, COMMAND_OFF) == 0) {
      setLightPointOff();
  } else {
    DiagnosticOutputStream.sendln("Unknown action '", command, "' for point ", objectFullRemoteName);
  };
}
