/*
 * ConfigurationReader.h
 *
 * Class created to define API to read configuration from SD card. Configuration is stored
 * as JSON file in following directory:
 *
 * /calldomi/config.json
 *
 *
 *  Created on: Jan 21, 2016
 *      Author: siwecki
 */

#ifndef CONFIGURATIONREADER_H_
#define CONFIGURATIONREADER_H_

#include <SD.h>
#include "Actor.h"

const String FILE_CONFIG_LOCATION = "/calldomi/config.json";

class ConfigurationReader {
public:
	ConfigurationReader();
	virtual ~ConfigurationReader();

	void fillUsingConfiguraion(Actor* actor);
};

#endif /* CONFIGURATIONREADER_H_ */
