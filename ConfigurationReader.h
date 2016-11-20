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
#include "Room.h"
#include "Configuration.h"
#include "ArduinoJson.h"

class ConfigurationReader {
private:
	bool readToBuffer(File* file, char* fileContentBuffer);
	bool readHome(File* myFile, char* fileContentBuffer, Actor* actor, Configuration* config);
	void readConfig(JsonObject& , Configuration* config);
	void readRooms(JsonArray& rooms, Actor* actor);
	void readPoints(JsonArray& points, Room* actor);

public:
	ConfigurationReader();
	virtual ~ConfigurationReader();

	bool readConfigurationFromFile(Actor* actor, Configuration* config);
};

#endif /* CONFIGURATIONREADER_H_ */
