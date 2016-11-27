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
	send(value);
	sendln();
}

void GeneralOutputStream::sendln(const char * value1, const char * value2) {
	send(value1, value2);
	sendln();
}

void GeneralOutputStream::sendln(const char * value1, const char * value2, const char * value3) {
	send(value1, value2, value3);
	sendln();
}

void GeneralOutputStream::sendln(const char * value1, const char * value2, const char * value3, const char * value4) {
	send(value1, value2, value3, value4);
	sendln();
}

void GeneralOutputStream::sendln(const char * value1, const char * value2, const char * value3, int value4) {
	send(value1, value2, value3);
	send(value4);
	sendln();
}

void GeneralOutputStream::sendln(const char * value1, int value2, int value3, int value4, int value5, int value6 , int value7) {
	if (!sendToSerial) {
		return;
	}
	if (value1 != NULL) {
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

void GeneralOutputStream::send(const char * value) {
	if (sendToSerial) {
		Serial.print(value);
	}
}

void GeneralOutputStream::send(const int value) {
	if (sendToSerial) {
		Serial.print(value);
	}
}

void GeneralOutputStream::sendln() {
	if (sendToSerial) {
		Serial.println();
	}
}

void GeneralOutputStream::send(const char * value1, const char * value2) {
	if (!sendToSerial) {
		return;
	}
	if (value1 != NULL) {
		Serial.print(value1);
	}
	if (value2 != NULL) {
		Serial.print(value2);
	}
}

void GeneralOutputStream::send(const char * value1, const char * value2, const char * value3) {
	if (!sendToSerial) {
		return;
	}
	if (value1 != NULL) {
		Serial.print(value1);
	}
	if (value2 != NULL) {
		Serial.print(value2);
	}
	if (value3 != NULL) {
		Serial.print(value3);
	}
}

void GeneralOutputStream::send(const char * value1, const char * value2, const char * value3, const char * value4) {
	if (!sendToSerial) {
		return;
	}
	if (value1 != NULL) {
		Serial.print(value1);
	}
	if (value2 != NULL) {
		Serial.print(value2);
	}
	if (value3 != NULL) {
		Serial.print(value3);
	}
	if (value4 != NULL) {
		Serial.print(value4);
	}
}





