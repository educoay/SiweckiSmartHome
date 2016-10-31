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

class ConfigurationReader {
private:
	void readHome(File* myFile, Actor* actor, Configuration* config);
	void readConfig(File* myFile, Configuration* config);
	void readRooms(File* myFile, Actor* actor);
	void readRoom(File* myFile, Actor* actor);
	void readPoints(File* myFile, Room* actor);
	void readPoint(File* myFile, Room* actor);

public:
	ConfigurationReader();
	virtual ~ConfigurationReader();

	bool readConfiguraionFromFile(Actor* actor, Configuration* config);
};

#endif /* CONFIGURATIONREADER_H_ */
