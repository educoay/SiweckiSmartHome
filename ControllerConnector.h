/*
  ControllerConnector.h - Connector for controller. Implementation done via MQTT with OpenHAB
  Created by Piotr Kaminski, 2015/07/12.
*/
#ifndef ControllerConnector_h
#define ControllerConnector_h

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

class ControllerConnector {
  private:
    byte mac[6] = {0x00, 0x12, 0xFB, 0x95, 0x59, 0xCF};

    char* queueController = "/SSH/ToController";
    char* listenQueueRange = "/SSH/#";
    char* clientName = "SSH-Actor01";
    char* mqttServerUsername = "anonymous";
    char* mqttServerPassword = "haslo";
    EthernetClient ethClient;
    PubSubClient *mqttClient = NULL;

    void initializeMqtt();
    
  public:
    ControllerConnector();
    ~ControllerConnector();
    void setMqttClient(PubSubClient *_mqttClient) {this->mqttClient = _mqttClient;};
    void sendCommand(String command);
    void initialize();
    boolean checkOutstandingMessages();
};

#endif
