/*
 * Configuration.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: siwecki
 */

#include "Configuration.h"

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	delete this->instanceName;
}

void Configuration::setInstanceName(char* _name) {
	this->instanceName = strdup(_name);
}

