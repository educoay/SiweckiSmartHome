
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
  Serial.println("ControllerConnector init... ");

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
  DiagnosticOutputStream.sendln("ControllerConnector init done.");
}

 
void ControllerConnector::initializeMqtt()
{
  Serial.println("Init MQTT...");
  if (this->mqttClient != NULL) {
    if (mqttClient->connect(this->clientName, this->mqttServerUsername, this->mqttServerPassword)) {
      DiagnosticOutputStream.sendln("Subscribe queue range: ", this->listenQueueRange);
      mqttClient->subscribe(this->listenQueueRange);
      DiagnosticOutputStream.sendln("MQTT connect OK");
    } else {
    	DiagnosticOutputStream.sendln("MQTT connect failed");
    }
  } else {
	  DiagnosticOutputStream.sendln("mqttClient is null");
  }
}

boolean ControllerConnector::checkOutstandingMessages() {
  return mqttClient->loop();
}

void ControllerConnector::sendCommand(char* queue, char* command) {
  DiagnosticOutputStream.sendln("Command to send: ", queue, " ", command);

  if (!mqttClient->connected()) {
     initializeMqtt();
  }
  
  if (mqttClient->publish(queue, command)) {
	  DiagnosticOutputStream.sendln("Command ", queue, " published.");
  } else {
	  DiagnosticOutputStream.sendln("Command ", queue, " publish failed.");
  } 
}
