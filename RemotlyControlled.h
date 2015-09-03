#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

class RemotlyControlled {
  protected:
    String name;
    RemotlyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    RemotlyControlled(String _name) { this->name = _name;};
    String getNextRemotlyControlled(String queue);
    String getSubRemotlyControlled(String queue);
    void setParent(RemotlyControlled *_parent) {this->parent = _parent;} ;
    void setControllerConnector(ControllerConnector *_controllerConnector) {this->controllerConnector = _controllerConnector;};
    String getRemoteName();
    void sendStateUpdate();
    virtual String getFullRemoteName();
    virtual String createCommand() = 0;
    virtual String createQueue() = 0;
    virtual void executeCommand(String queue, String command) = 0;
 };

 #endif
