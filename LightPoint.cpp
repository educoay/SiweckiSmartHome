#include "LightPoint.h"

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, String name):Point(name) {
	this->controlButtonPin = controlButtonPin;
	this->controlOutputPin = controlOutputPin;
}

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, String name, ControllerConnector *controllerConnector):Point(name) {
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
        Serial.println(this->getFullRemoteName() + " button pressed");
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
  Serial.println(getFullRemoteName() + " on.");
}

void LightPoint::setLightPointOff() {
  setLightPointState(LOW);
  Serial.println(getFullRemoteName() + " off.");
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

String LightPoint::createQueue() {
  return getFullRemoteName();
}

String LightPoint::createCommand(int state) {
	if (state == LOW) {
		return COMMAND_OFF;
	} else {
		return COMMAND_ON;
	}
}

String LightPoint::createCommand() {
  return createCommand(this->lightPointState);
}

void LightPoint::executeCommand(String queue, String command) {
  if (command == COMMAND_ON) {
      setLightPointOn();
  } else if (command == COMMAND_OFF) {
      setLightPointOff();
  } else {
    Serial.println("Unknown action '" + command + "' for point " + getFullRemoteName());
  };
  //Serial.println("Action " + command + " finished");
}
