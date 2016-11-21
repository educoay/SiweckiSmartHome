/*
 * Configuration.h
 *
 *  Created on: Jan 30, 2016
 *      Author: siwecki
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Arduino.h"

class Configuration {
public:
	byte mac[6];// = {0x00, 0x12, 0xFB, 0x95, 0x59, 0xCF};
	unsigned int mqttServerIP[4]; // = {192, 168, 1, 190};
	int mqttServerPort = 1883;
	bool isDebug = true;
	char* instanceName;

	Configuration();
	virtual ~Configuration() ;
	void setInstanceName(char* _name);
};

#endif /* CONFIGURATION_H_ */
