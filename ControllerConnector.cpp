
#include "ControllerConnector.h"
#include "Actor.h"
#include "Const.h"
#include "GeneralOutputStream.h"

static const char* ANY_QUEUE_WILDCARD = "#";

ControllerConnector::ControllerConnector() {
  this->mqttClient = NULL;
  this->clientName = NULL;
  this->listenQueueRange = NULL;
}

ControllerConnector::~ControllerConnector() {
  delete this->mqttClient;
  delete this->clientName;
  delete this->listenQueueRange;
}

void ControllerConnector::initialize(const char* connectivityClientName) {
  Serial.println("CtrConn init");

  //make a copy of clientName
  delete this->clientName;
  this->clientName = strdup(connectivityClientName);

  delete this->listenQueueRange;
  this->listenQueueRange = new char[
									strlen(LOCATION_DELIMETER) +
									strlen(this->clientName) +
									strlen(LOCATION_DELIMETER) +
									strlen(IN_DIRECTION) +
									strlen(LOCATION_DELIMETER) +
									strlen(ANY_QUEUE_WILDCARD) +
									1];

  strcpy(this->listenQueueRange, LOCATION_DELIMETER);
  strcat(this->listenQueueRange, this->clientName);
  strcat(this->listenQueueRange, LOCATION_DELIMETER);
  strcat(this->listenQueueRange, IN_DIRECTION);
  strcat(this->listenQueueRange, LOCATION_DELIMETER);
  strcat(this->listenQueueRange, ANY_QUEUE_WILDCARD);
  DiagnosticOutputStream.sendln("Queue: ", this->listenQueueRange);
  
  initializeMqtt();
  DiagnosticOutputStream.sendln("CtrConn init done");
}

 
void ControllerConnector::initializeMqtt()
{
  if (this->mqttClient != NULL) {
    if (mqttClient->connect(this->clientName, this->mqttServerUsername, this->mqttServerPassword)) {
      DiagnosticOutputStream.sendln("Subscribe queue range: ", this->listenQueueRange);
      mqttClient->subscribe(this->listenQueueRange);
      DiagnosticOutputStream.sendln("MQTT conn OK");
    } else {
    	DiagnosticOutputStream.sendln("MQTT conn failed");
    }
  } else {
	  DiagnosticOutputStream.sendln("no mqttClient");
  }
}

boolean ControllerConnector::checkOutstandingMessages() {
  return mqttClient->loop();
}

void ControllerConnector::sendCommand(char* queue, char* command) {
  if (!mqttClient->connected()) {
     initializeMqtt();
  }
  
  if (mqttClient->publish(queue, command)) {
	  DiagnosticOutputStream.sendln("Msg pub ok: ", queue, ":", command);
  } else {
	  DiagnosticOutputStream.sendln("Msg pub failed: ", queue, ":", command);
  } 
}
