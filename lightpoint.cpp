#include "LightPoint.h"

LightPoint::LightPoint(int controlButtonPin, int controlOutputPin, String name) {
	this->controlButtonPin = controlButtonPin;
	this->controlOutputPin = controlOutputPin;
  this->name = name;
	initialize();
}

void LightPoint::initialize() {
    pinMode(this->controlButtonPin, INPUT);
    pinMode(this->controlOutputPin, OUTPUT);
    setLightPointState(LOW);
}

int LightPoint::checkControlButton() {
  return digitalRead(this->controlButtonPin);
}
 
void LightPoint::setLightPointState(int state) {
    digitalWrite(this->controlOutputPin, state);
    this->lightPointState = state;
}

String LightPoint::createCommand(int state) {
	String command = this->name + COMMAND_DELIMETER;
	if (state == LOW) {
		return command + COMMAND_OFF;
	} else {
		return command + COMMAND_ON;
	}
}
