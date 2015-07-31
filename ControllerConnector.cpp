
#include "ControllerConnector.h"
#include "RealEstate.h"

extern RealEstate realEstate;

ControllerConnector::ControllerConnector() {
  this->mqttClient = NULL;
}

ControllerConnector::~ControllerConnector() {
  delete this->mqttClient;
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  char* strPayload = (char*)payload;
  Serial.print("IN: ");
  Serial.println(strPayload);
  //realEstate.executeCommand(strPayload);
}

void ControllerConnector::initialize() {
  Serial.println("ControllerConnector initialization... ");
  Serial.println("Init Ehternet...");
  Ethernet.begin(this->mac, this->ip);
  Serial.println("Init MQTT...");
  //initializeMqtt();
  Serial.println("ControllerConnector initialization done.");
}

 
void ControllerConnector::initializeMqtt()
{
  if (mqttClient != NULL ){
    delete mqttClient;
    mqttClient = NULL;
  }
  
  mqttClient = new PubSubClient(mqttServerIP, mqttServerPort, callback, ethClient);

  mqttClient->connect("arduinoClient", "anonymous", "haslo");
  /*
  if (mqttClient->connect("arduinoClient", "anonymous", "haslo")) {
    mqttClient->subscribe(queueActor);
    Serial.println("MQTT connect OK");
  } else {
    Serial.println("MQTT connect failed");
  }
  */
}

boolean ControllerConnector::checkOutstandingMessages() {
  return mqttClient->loop();
}

void ControllerConnector::sendCommand(String command) {
  Serial.println("Command to send to Controller: " + command);

  boolean connected = mqttClient->connected();
  if (!connected) {
     initializeMqtt();
  }
  char ssid[command.length() + 1];        
  command.toCharArray(ssid, command.length() + 1);
  boolean publishState = mqttClient->publish(queueController, ssid); 
  Serial.println("Published with result " + publishState);    
}
