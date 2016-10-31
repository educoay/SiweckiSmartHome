/*
 * ConfigurationReader.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: siwecki
 */

#include "ConfigurationReader.h"
#include "GeneralOutputStream.h"

#define FILE_CONFIG_LOCATION "config.jso"
#define SD_SS_PIN 53
#define READ_FILE_BUFFOR_SIZE 150

ConfigurationReader::ConfigurationReader() {

}

ConfigurationReader::~ConfigurationReader() {
}

void ConfigurationReader::readHome(File* myFile, Actor* actor, Configuration* config) {
	readConfig(myFile, config);
	readRooms(myFile, actor);

}

void ConfigurationReader::readConfig(File* myFile, Configuration* config) {

}

void ConfigurationReader::readRooms(File* myFile, Actor* actor) {
	readRoom(myFile, actor);
}

void ConfigurationReader::readRoom(File* myFile, Actor* actor) {
	Room* room;
	readPoints(myFile, room);
}

void ConfigurationReader::readPoints(File* myFile, Room* room) {
	readPoint(myFile, room);
}

void ConfigurationReader::readPoint(File* myFile, Room* room) {

}


bool ConfigurationReader::readConfiguraionFromFile(Actor* actor, Configuration* config) {
	if (!SD.begin(SD_SS_PIN)) {
		DiagnosticOutputStream.sendln("No SD");
		return false;
	};

	//open config file from SD card
	File myFile = SD.open(FILE_CONFIG_LOCATION);

	if (myFile) {
		//read configuration from config file
		readHome(&myFile, actor, config);

		// close the file:
		myFile.close();
	} else {
		// if the file didn't open, print an error:
		DiagnosticOutputStream.sendln("Err opening conf file ", FILE_CONFIG_LOCATION);
		return false;
	}
	DiagnosticOutputStream.sendln("Conf read from file ", FILE_CONFIG_LOCATION);
	return true;
}

