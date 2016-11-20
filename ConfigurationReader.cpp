/*
 * ConfigurationReader.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: siwecki
 */

#include "ConfigurationReader.h"
#include "GeneralOutputStream.h"
#include "ArduinoJson.h"

#define FILE_CONFIG_LOCATION "config.jso"
#define SD_SS_PIN 53
#define READ_FILE_BUFFOR_SIZE 1024

#define JSON_HOME "Home"
#define JSON_CONFIG "Conf"
#define JSON_INSTANCE_NAME "Name"
#define JSON_DEBUG "Debug"
#define JSON_MAC "Mac"
#define JSON_MQTT_IP "MQTT-IP"
#define JSON_MQTT_PORT "MQTT-Port"

ConfigurationReader::ConfigurationReader() {

}

ConfigurationReader::~ConfigurationReader() {
}


void ConfigurationReader::skipTillChar(File* file, char charToSkip, short numOfChars) {
	bool stop = false;
	char fileChar;
	short num = 0;
	while(!stop && file->available()) {
		fileChar = file->read();
		if (fileChar == charToSkip) {
			num++;
		}
		if (num >= numOfChars) {
			stop = true;
		}
	}
}


bool ConfigurationReader::readToBuffer(File* file, char* fileContentBuffer) {
	char fileChar;
	int index = 0;
	while(file->available() && index < READ_FILE_BUFFOR_SIZE) {
		fileChar = file->read();
		if (!isspace(fileChar)) {
			fileContentBuffer[index++] = fileChar;
		}
	}
	fileContentBuffer[index] = '\0';

	if (file->available()) {
		DiagnosticOutputStream.sendln("Not all config loaded");
		return false;
	}
	return true;
}

bool ConfigurationReader::readToBufferTillChar(File* file, char* fileContentBuffer, char charToStop) {
	char fileChar;
	uint8_t index = 0;
	while(file->available() && charToStop != fileChar) {
		fileChar = file->read();
		if (!isspace(fileChar)) {
			fileContentBuffer[index++] = fileChar;
		}
	}
	fileContentBuffer[index] = '\0';
	return true;
}

bool ConfigurationReader::readHome(File* file, char* fileContentBuffer, Actor* actor, Configuration* config) {
	if (!readToBuffer(file, fileContentBuffer)) {
		return false;
	}
	DiagnosticOutputStream.sendln(fileContentBuffer);
	StaticJsonBuffer<READ_FILE_BUFFOR_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(fileContentBuffer);

	if (!root.success()) {
	  DiagnosticOutputStream.sendln("Config parse failed");
	  return false;
	}

	config->isDebug 		= root[JSON_HOME][JSON_CONFIG][JSON_DEBUG];
	config->mqttServerPort 	= root[JSON_HOME][JSON_CONFIG][JSON_MQTT_PORT];
}


void ConfigurationReader::readConfig(File* file, char* fileContentBuffer, Configuration* config) {
	readToBufferTillChar(file, fileContentBuffer, '}');
	DiagnosticOutputStream.sendln("Conf:", fileContentBuffer);


	StaticJsonBuffer<READ_FILE_BUFFOR_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(fileContentBuffer);

	if (!root.success()) {
	  DiagnosticOutputStream.sendln("Config parse failed.");
	  return;
	}

	config->isDebug = root[JSON_DEBUG];
}

void ConfigurationReader::readRooms(File* file, char* fileContentBuffer, Actor* actor) {
	char fileChar = ' ';
	skipTillChar(file, '[', 1);
	do {
		readRoom(file, fileContentBuffer, actor);
		fileChar = file->read();
	} while (fileChar == ',');
}

void ConfigurationReader::readRoom(File* myFile, char* fileContentBuffer, Actor* actor) {
	Room* room;
	readPoints(myFile, fileContentBuffer, room);
}

void ConfigurationReader::readPoints(File* file, char* fileContentBuffer, Room* room) {
	readPoint(file, fileContentBuffer, room);
}

void ConfigurationReader::readPoint(File* file, char* fileContentBuffer, Room* room) {

}


bool ConfigurationReader::readConfigurationFromFile(Actor* actor, Configuration* config) {
	if (!SD.begin(SD_SS_PIN)) {
		DiagnosticOutputStream.sendln("No SD");
		return false;
	};

	//open config file from SD card
	File file = SD.open(FILE_CONFIG_LOCATION);


	if (file) {
		//read configuration from config file
		char fileContentBuffer[READ_FILE_BUFFOR_SIZE];
		readHome(&file, fileContentBuffer, actor, config);
		// close the file:
		file.close();
	} else {
		// if the file didn't open, print an error:
		DiagnosticOutputStream.sendln("Err opening conf file ", FILE_CONFIG_LOCATION);
		return false;
	}
	DiagnosticOutputStream.sendln("Conf read from file ", FILE_CONFIG_LOCATION);
	return true;
}

