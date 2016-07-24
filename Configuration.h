/*
 * Configuration.h
 *
 *  Created on: Jan 30, 2016
 *      Author: siwecki
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

class Configuration {
public:
	int mac[6];
	int mqttServerIP[4] = {192, 168, 1, 190};
	int mqttServerPort = 1883;
	int AFTER_CHANGE_DELAY = 100;

	Configuration();
	virtual ~Configuration();
};

#endif /* CONFIGURATION_H_ */
