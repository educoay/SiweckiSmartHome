
#include "ControllerConnector.h"
#include "Actor.h"

ControllerConnector::ControllerConnector() {
  this->mqttClient = NULL;

}

ControllerConnector::~ControllerConnector() {
  delete this->mqttClient;
}

void ControllerConnector::initialize(String actorName) {
  Serial.println("ControllerConnector init... ");

  actorName.toCharArray(this->clientName, actorName.length() + 1);
  String sListenQueueRange = LOCATION_DELIMETER + actorName 
                + LOCATION_DELIMETER + IN_DIRECTION + LOCATION_DELIMETER + '#';
  delete this->listenQueueRange;
  this->listenQueueRange = new char[sListenQueueRange.length() + 1];
  sListenQueueRange.toCharArray(this->listenQueueRange, sListenQueueRange.length() + 1);
  Serial.println("Queue: " + sListenQueueRange);
  
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

void ControllerConnector::sendCommand(String queue, String command) {
  Serial.println("Command to send: " + queue + " " + command);

  if (!mqttClient->connected()) {
     initializeMqtt();
  }


  char cCommand[command.length() + 1];        
  command.toCharArray(cCommand, command.length()+1);
  char qQueue[queue.length() + 1];        
  queue.toCharArray(qQueue, queue.length()+1);
  
  if (mqttClient->publish(qQueue, cCommand)) {
      Serial.print("Command "); 
      Serial.print(qQueue);
      Serial.println(" published."); 
  } else {
      Serial.print("Command "); 
      Serial.print(qQueue);
      Serial.println(" publish failed."); 
  } 
}
