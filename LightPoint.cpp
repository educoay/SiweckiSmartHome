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

String LightPoint::createCommand(int state) {
	String command = getFullRemoteName() + STATE_DELIMETER;
	if (state == LOW) {
		return command + COMMAND_OFF;
	} else {
		return command + COMMAND_ON;
	}
}

String LightPoint::createCommand() {
  return createCommand(this->lightPointState);
}

void LightPoint::executeCommand(String action) {
  if (action == COMMAND_ON) {
      setLightPointOn();
  } else if (action == COMMAND_OFF) {
      setLightPointOff();
  } else {
    Serial.println("Unknown action '" + action + "' for point " + getFullRemoteName());
  };
  //Serial.println("Action " + action + " finished");
}
