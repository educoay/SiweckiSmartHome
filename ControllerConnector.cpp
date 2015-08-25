
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

  boolean connected = mqttClient->connected();
  if (!connected) {
     initializeMqtt();
  }
  char ssid[command.length() + 1];        
  command.toCharArray(ssid, command.length() + 1);
  boolean publishState = mqttClient->publish(this->queueController, ssid); 
  
  if (publishState) {
      Serial.println("Command " + command + " published."); 
  } else {
    Serial.println("Command " + command + " publish failed."); 
  }   
}
