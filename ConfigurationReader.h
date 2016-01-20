/*
 * ConfigurationReader.h
 *
 * Reads configuration from SD card. Configuration is stored as JSON document in ssh.config file in main folder.
 * Structure of config file is as follow:
 *
 *
 *  Created on: Jan 19, 2016
 *      Author: siwecki
 */

#ifndef CONFIGURATIONREADER_H_
#define CONFIGURATIONREADER_H_

class ConfigurationReader {
public:
	ConfigurationReader();
	virtual ~ConfigurationReader();

	/**
	 * Creates
	 * @return
	 */
	Actor* createActorBasingOnConfigFile();
};

#endif /* CONFIGURATIONREADER_H_ */
