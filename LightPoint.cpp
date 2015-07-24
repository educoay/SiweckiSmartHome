#include "LightPoint.h"

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, String name):Point(name) {
	this->controlButtonPin = controlButtonPin;
	this->controlOutputPin = controlOutputPin;
	initialize();
}

LightPoint::~LightPoint() {
}


void LightPoint::initialize() {
    pinMode(this->controlButtonPin, INPUT);
    pinMode(this->controlOutputPin, OUTPUT);
    setLightPointState(LOW);
}

boolean LightPoint::isControlButtonPressed() {
  int buttonNow =  digitalRead(this->controlButtonPin);
  //Serial.print("buttonNow: ");
  //Serial.println(buttonNow);
  
  if (buttonNow != this->buttonPreviousState) {
    this->buttonPreviousState = buttonNow;
    if(buttonNow == HIGH) {
        Serial.println("--> " + getObjectName() + "Button pressed event <--");
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
  Serial.println("Light switch on.");
}

void LightPoint::setLightPointOff() {
  setLightPointState(LOW);
    Serial.println("Light switched off.");
}
 
void LightPoint::setLightPointState(int state) {
    digitalWrite(this->controlOutputPin, state);
    this->lightPointState = state;
}

void LightPoint::verifyControlPoint() {
  if (isControlButtonPressed()) {
    Serial.println(getObjectName() + " control button pressed");
    if (isLightPointOn()) {
      setLightPointOff();
    } else {
      setLightPointOn();
    }
  }
}

String LightPoint::getObjectName() {
  return commandParent->getObjectName() + LOCATION_DELIMETER + this->name;
}

String LightPoint::createCommand(int state) {
	String command = getObjectName() + STATE_DELIMETER;
	if (state == LOW) {
		return command + COMMAND_OFF;
	} else {
		return command + COMMAND_ON;
	}
}

String LightPoint::createCommand() {
  return createCommand(this->lightPointState);
}
