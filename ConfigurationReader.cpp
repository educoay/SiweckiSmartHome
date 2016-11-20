/*
 * ConfigurationReader.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: siwecki
 */

#include "ConfigurationReader.h"
#include "GeneralOutputStream.h"
#include "LightPoint.h"

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
#define JSON_ROOMS "Rooms"
#define JSON_ROOM_NAME "Name"
#define JSON_POINTS "Points"
#define JSON_POINT_NAME "Name"
#define JSON_POINT_TYPE "Type"
#define JSON_POINT_TYPE_LIGHT "Light"
#define JSON_POINT_CTRPIN "CtrPin"
#define JSON_POINT_BTNPIN "BtnPin"

ConfigurationReader::ConfigurationReader() {

}

ConfigurationReader::~ConfigurationReader() {
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



bool ConfigurationReader::readHome(File* file, char* fileContentBuffer, Actor* actor, Configuration* config) {
	if (!readToBuffer(file, fileContentBuffer)) {
		return false;
	}
	//DiagnosticOutputStream.sendln(fileContentBuffer);
	StaticJsonBuffer<READ_FILE_BUFFOR_SIZE> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(fileContentBuffer);

	if (!root.success()) {
	  DiagnosticOutputStream.sendln("Config parse failed");
	  return false;
	}
	readConfig(root, config);
	JsonArray& jsonRooms = root[JSON_ROOMS].asArray();
	readRooms(jsonRooms, actor);
}


void ConfigurationReader::readConfig(JsonObject& root, Configuration* config) {
	config->isDebug 		= root[JSON_HOME][JSON_CONFIG][JSON_DEBUG];
	//DiagnosticOutputStream.sendln("debug", config->isDebug ? "ok" : "nok");

	//parse mac address of Ethernet sheld
	const char* mac = root[JSON_HOME][JSON_CONFIG][JSON_MAC];
	char *smac_start, *smac_end;
	smac_start = mac; smac_end = strchr(smac_start, ':');
	config->mac[0] = (byte)strtol(smac_start, &smac_end, 16);
	smac_start = smac_end+1; smac_end = strchr(smac_start, ':');
	config->mac[1] = (byte)strtol(smac_start, &smac_end, 16);
	smac_start = smac_end+1; smac_end = strchr(smac_start, ':');
	config->mac[2] = (byte)strtol(smac_start, &smac_end, 16);
	smac_start = smac_end+1; smac_end = strchr(smac_start, ':');
	config->mac[3] = (byte)strtol(smac_start, &smac_end, 16);
	smac_start = smac_end+1; smac_end = strchr(smac_start, ':');
	config->mac[4] = (byte)strtol(smac_start, &smac_end, 16);
	smac_start = smac_end+1; smac_end = strchr(smac_start, ':');
	config->mac[5] = (byte)strtol(smac_start, &smac_end, 16);
//	DiagnosticOutputStream.sendln("mac",
//			(int)config->mac[0],
//			(int)config->mac[1],
//			(int)config->mac[2],
//			(int)config->mac[3],
//			(int)config->mac[4],
//			(int)config->mac[5]);

	//parse ip address for mqtt server
	const char* ip = root[JSON_HOME][JSON_CONFIG][JSON_MQTT_IP];
	char *sip_start, *sip_end;
	sip_start = ip; sip_end = strchr(sip_start, '.');
	config->mqttServerIP[0] = strtol(sip_start, &sip_end, 10);
	sip_start = sip_end+1; strchr(sip_start, '.');
	config->mqttServerIP[1] = strtol(sip_start, &sip_end, 10);
	sip_start = sip_end+1; strchr(sip_start, '.');
	config->mqttServerIP[2] = strtol(sip_start, &sip_end, 10);
	sip_start = sip_end+1; strchr(sip_start, '.');
	config->mqttServerIP[3] = strtol(sip_start, &sip_end, 10);
//	DiagnosticOutputStream.sendln("ip",
//			(int)config->mqttServerIP[0],
//			(int)config->mqttServerIP[1],
//			(int)config->mqttServerIP[2],
//			(int)config->mqttServerIP[3],
//			0,0);


	//parse port for mqtt server
	config->mqttServerPort 	= root[JSON_HOME][JSON_CONFIG][JSON_MQTT_PORT];
}

void ConfigurationReader::readRooms(JsonArray& rooms, Actor* actor) {
	char *name;
	Room *room;
	for(JsonArray::iterator it=rooms.begin(); it!=rooms.end(); ++it)
	{
	    JsonObject &jsonRoom = it->asObject();
	    name = jsonRoom[JSON_ROOM_NAME];
	    room = new Room(name);
	    JsonArray& jsonPoints = jsonRoom[JSON_POINTS];
	    readPoints(jsonPoints, room);
	    actor->addRoom(room);
	}
}


void ConfigurationReader::readPoints(JsonArray& points, Room* room) {
	char *name;
	char *type;
	Point *point;
	int ctrPin, btnPin;
	for(JsonArray::iterator it=points.begin(); it!=points.end(); ++it)
	{
	    JsonObject &jsonPoint = it->asObject();
	    name = jsonPoint[JSON_POINT_NAME];
	    type = jsonPoint[JSON_POINT_TYPE];
	    ctrPin = jsonPoint[JSON_POINT_CTRPIN];
	    btnPin = jsonPoint[JSON_POINT_BTNPIN];

	    if (strcmp(type, JSON_POINT_TYPE_LIGHT) == 0) {
	    	point = new LightPoint(ctrPin, btnPin, name);
	    }
	    room->addPoint(point);
	}
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

