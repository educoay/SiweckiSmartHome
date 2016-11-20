/*
 * GeneralOutputStream.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: siwecki
 */

#include "Arduino.h"
#include "GeneralOutputStream.h"

GeneralOutputStream DiagnosticOutputStream;

void GeneralOutputStream::setSendToSerial(bool value) {
	sendToSerial = value;
}

void GeneralOutputStream::sendln(const char * value) {
	sendln(value, NULL, NULL, NULL);
}

void GeneralOutputStream::sendln(const char * value1, const char * value2) {
	sendln(value1, value2, NULL, NULL);
}

void GeneralOutputStream::sendln(const char * value1, const char * value2, const char * value3) {
	sendln(value1, value2, value3, NULL);
}

void GeneralOutputStream::sendln(const char * value1, const char * value2, const char * value3, const char * value4) {
	if (value1 != NULL && sendToSerial) {
				Serial.print(value1);
	}
	if (value2 != NULL && sendToSerial) {
				Serial.print(value2);
	}
	if (value3 != NULL && sendToSerial) {
				Serial.print(value3);
	}
	if (value4 != NULL && sendToSerial) {
				Serial.print(value4);
	}
	if (sendToSerial) {
		Serial.println();
	}
}

void GeneralOutputStream::sendln(const char * value1, int value2, int value3, int value4, int value5, int value6 , int value7) {
	if (value1 != NULL && sendToSerial) {
				Serial.print(value1);
	}
	Serial.print(';');Serial.print(value2);
	Serial.print(';');Serial.print(value3);
	Serial.print(';');Serial.print(value4);
	Serial.print(';');Serial.print(value5);
	Serial.print(';');Serial.print(value6);
	Serial.print(';');Serial.print(value7);
	Serial.println();
}






