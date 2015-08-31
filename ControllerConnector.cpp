
#include "ControllerConnector.h"
#include "RealEstate.h"

extern RealEstate realEstate;

ControllerConnector::ControllerConnector() {
  this->mqttClient = NULL;
}

ControllerConnector::~ControllerConnector() {
  delete this->mqttClient;
}



void ControllerConnector::initialize() {
  Serial.println("ControllerConnector init... ");
  initializeMqtt();
  Serial.println("ControllerConnector init done.");
}

 
void ControllerConnector::initializeMqtt()
{
  Serial.println("Init MQTT...");
  if (this->mqttClient != NULL) {
    if (mqttClient->connect(this->clientName, this->mqttServerUsername, this->mqttServerPassword)) {
      mqttClient->subscribe(this->queueActor);
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

void ControllerConnector::sendCommand(String command) {
  Serial.println("Command to send: " + command);

  if (!mqttClient->connected()) {
     initializeMqtt();
  }


  char message[command.length() + 1];        
  command.toCharArray(message, command.length()+1);
  
  if (mqttClient->publish(this->queueController, message)) {
      Serial.print("Command "); 
      Serial.print(message);
      Serial.println(" published."); 
  } else {
      Serial.print("Command "); 
      Serial.print(message);
      Serial.println(" publish failed."); 
  } 
}
