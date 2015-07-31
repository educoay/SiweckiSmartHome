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
    byte mqttServerIP[4] = {192, 168, 1, 190};
    int mqttServerPort = 1883;
    byte mac[6] = {0x00, 0x12, 0xFB, 0x95, 0x59, 0xCF};
    byte ip[4]  = {192, 168, 1, 191};
    char* queueController = "/SiweckiSmartHome/ToController";
    char* queueActor = "/SiweckiSmartHome/ToActor";
    EthernetClient ethClient; 
    PubSubClient *mqttClient = NULL;

    void initializeMqtt();
    
  public:
    ControllerConnector();
    ~ControllerConnector();
    void sendCommand(String command);
    void initialize();
    boolean checkOutstandingMessages();
};

#endif
