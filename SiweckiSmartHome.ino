#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "LightPoint.h"

const String QUEUE_SERVER = "/SiweckiSmartHome/ToServer";
const String QUEUE_ACTOR = "/SiweckiSmartHome/ToActor";

const String LIVINGROOM_NAME = "LIVINGROOM";
const int LIVINGROOM_BUTTON_PIN = 1;
const int LIVINGROOM_OUTPUT_PIN = 2;
const String KITCHEN_NAME = "KITCHEN";
const int KITCHEN_BUTTON_PIN = 1;
const int KITCHEN_OUTPUT_PIN = 2;

const int AFTER_CHANGE_DELAY = 500;

LightPoint livingRoom(LIVINROOM_BUTTON_PIN, LIVINGROOM_OUTPUT_PIN, LIVINGROOM_NAME);
//LightPoint kitchen(KITCHEN_BUTTON_PIN, KITCHEN_OUTPUT_PIN, KITCHEN_NAME);
 
//numer IP komputera na którym jest uruchomiony serwer mqtt
byte mqtt_server[] = { 192, 168, 1, 189};
byte mac[]    = {  0x00, 0x12, 0xFB, 0x95, 0x59, 0xCF };
byte ip[]     = { 192, 168, 1, 191 }; 
 
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  initializeMqtt();
  livingRoom.initialize();
}
 
void loop() {
  checkMqtt();
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strPayload = String((char*)payload);
  Serial.print("IN: ");
  Serial.println(strPayload);
  executeRemoteCommand(strPayload);  
}
 
EthernetClient ethClient; 
PubSubClient mqtt_client(mqtt_server, 1883, callback, ethClient);
 
void sendMqttState(String state) {
  Serial.print("STATE: ");
  Serial.print(state);
  /*
  konieczna weryfikacja czy mamy aktywne połączenie
  jeśli nie, trzeba je odnowić
  */
  boolean connected = mqtt_client.connected();
  if (!connected) {
     initializeMqtt();
  }
  char ssid[state.length()+1];        
  state.toCharArray(ssid, state.length()+1);
  boolean publishState = mqtt_client.publish(&QUEUE_SERVER, ssid); 
  Serial.print(" published: ");
  Serial.println(publishState);
}
 
void initializeMqtt()
{
  if (mqtt_client.connect("arduinoClient", "anonymous", "haslo")) {
    mqtt_client.subscribe("/house");
    Serial.println("MQTT connect OK");
  } else {
    Serial.println("MQTT connect failed");
  }
}
 
void checkMqtt()
{
  mqtt_client.loop();
}
 
void executeRemoteCommand(String command) {
  Serial.println(command);
  if (command == HALOGEN_ON_COMMAND) {
    setHalogenState(HIGH);
  }
  if (command == HALOGEN_OFF_COMMAND) {
    setHalogenState(LOW);
  }
}

 

 
