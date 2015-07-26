
#include "ControllerConnector.h"
#include "RealEstate.h"

extern RealEstate realEstate;

ControllerConnector::ControllerConnector() {
  this->mqttClient = NULL;
  mqttServerIP[0] = 192;
  mqttServerIP[1] = 168;
  mqttServerIP[2] = 1;
  mqttServerIP[3] = 190;
  mqttServerPort = 1883;
  mac[0]    = 0x00;
  mac[1]    = 0x12;
  mac[2]    = 0xFB;
  mac[3]    = 0x95;
  mac[4]    = 0x59;
  mac[5]    = 0xCF;
  ip[0]     = 192; 
  ip[1]     = 168; 
  ip[2]     = 1; 
  ip[3]     = 191; 
}

ControllerConnector::~ControllerConnector() {
  delete this->mqttClient;
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  char* strPayload = (char*)payload;
  Serial.print("IN: ");
  Serial.println(strPayload);
  realEstate.executeCommand(strPayload);
}

void ControllerConnector::initialize() {
  Ethernet.begin(this->mac, this->ip);
  initializeMqtt();
}

 
void ControllerConnector::initializeMqtt()
{
  if (mqttClient != NULL ){
    delete mqttClient;
  }
  mqttClient = new PubSubClient(mqttServerIP, mqttServerPort, callback, ethClient);
  
  if (mqttClient->connect("arduinoClient", "anonymous", "haslo")) {
    mqttClient->subscribe(queueActor);
    Serial.println("MQTT connect OK");
  } else {
    Serial.println("MQTT connect failed");
  }
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
