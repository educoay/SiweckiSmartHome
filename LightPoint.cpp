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
        Serial.println("--> " + getRemoteName() + "Button pressed event <--");
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
    sendStateUpdate();
}

void LightPoint::verifyControlPoint() {
  if (isControlButtonPressed()) {
    Serial.println(getRemoteName() + " control button pressed");
    if (isLightPointOn()) {
      setLightPointOff();
    } else {
      setLightPointOn();
    }
  }
}

String LightPoint::getRemoteName() {
  if (parent != NULL) {
    return parent->getRemoteName() + LOCATION_DELIMETER + this->name;
  } else {
    return "";
  }
}

String LightPoint::createCommand(int state) {
	String command = getRemoteName() + STATE_DELIMETER;
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
    Serial.println("Unknown action '" + action + "' for point " + getRemoteName());
  }
}
