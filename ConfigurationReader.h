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
	void skipTillChar(File* file, char charToSkip, short numOfChars);
	bool readToBuffer(File* file, char* fileContentBuffer);
	bool readToBufferTillChar(File* file, char* fileContentBuffer, char charToStop);

	bool readHome(File* myFile, char* fileContentBuffer, Actor* actor, Configuration* config);

	void readConfig(File* myFile, char* fileContentBuffer, Configuration* config);
	void readRooms(File* myFile, char* fileContentBuffer, Actor* actor);
	void readRoom(File* myFile, char* fileContentBuffer, Actor* actor);
	void readPoints(File* myFile, char* fileContentBuffer, Room* actor);
	void readPoint(File* myFile, char* fileContentBuffer, Room* actor);

public:
	ConfigurationReader();
	virtual ~ConfigurationReader();

	bool readConfigurationFromFile(Actor* actor, Configuration* config);
};

#endif /* CONFIGURATIONREADER_H_ */
