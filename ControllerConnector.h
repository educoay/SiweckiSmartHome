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
    byte mqttServerIP[];
    int mqttServerPort = 1883;
    byte mac[];
    byte ip[]; 
    char* queueController = "/SiweckiSmartHome/ToController";
    char* queueActor = "/SiweckiSmartHome/ToActor";
    EthernetClient ethClient; 
    PubSubClient *mqttClient;

    void initializeMqtt();
    
  public:
    ControllerConnector();
    ~ControllerConnector();
    //void callback(char* topic, byte* payload, unsigned int length);
    void sendCommand(String command);
    void initialize();
    boolean checkOutstandingMessages();
};

#endif
