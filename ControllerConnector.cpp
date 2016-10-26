
#include "ControllerConnector.h"
#include "Actor.h"
#include "Const.h"

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
  strcpy(this->listenQueueRange,LOCATION_DELIMETER);
  strcpy(this->listenQueueRange,this->clientName);
  strcpy(this->listenQueueRange,LOCATION_DELIMETER);
  strcpy(this->listenQueueRange,IN_DIRECTION);
  strcpy(this->listenQueueRange,LOCATION_DELIMETER);
  strcpy(this->listenQueueRange,ANY_QUEUE_WILDCARD);
  Serial.print("Queue: ");
  Serial.println(this->listenQueueRange);
  
  initializeMqtt();
  Serial.println("ControllerConnector init done.");
}

 
void ControllerConnector::initializeMqtt()
{
  Serial.println("Init MQTT...");
  if (this->mqttClient != NULL) {
    if (mqttClient->connect(this->clientName, this->mqttServerUsername, this->mqttServerPassword)) {
      Serial.print("Subscribe queue range: ");
      Serial.println(this->listenQueueRange);
      mqttClient->subscribe(this->listenQueueRange);
      Serial.println("MQTT connect OK");
    } else {
      Serial.println("MQTT connect failed");
    }
  } else {
    Serial.println("mqttClient is null");
  }
}

boolean ControllerConnector::checkOutstandingMessages() {
  return mqttClient->loop();
}

void ControllerConnector::sendCommand(char* queue, char* command) {
  Serial.print("Command to send: ");
  Serial.print(queue);
  Serial.print(" ");
  Serial.println(command);

  if (!mqttClient->connected()) {
     initializeMqtt();
  }
  
  if (mqttClient->publish(queue, command)) {
      Serial.print("Command "); 
      Serial.print(queue);
      Serial.println(" published."); 
  } else {
      Serial.print("Command "); 
      Serial.print(queue);
      Serial.println(" publish failed."); 
  } 
}
