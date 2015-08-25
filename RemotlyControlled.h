#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

const char STATE_DELIMETER = '#';
const char LOCATION_DELIMETER = '.';

class RemotlyControlled {
  protected:
    String name;
    RemotlyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    RemotlyControlled(String _name) { this->name = _name;};
    String getNextRemotlyControlled(String command);
    String getSubCommand(String command);
    void setParent(RemotlyControlled *_parent) {this->parent = _parent;} ;
    void setControllerConnector(ControllerConnector *_controllerConnector) {this->controllerConnector = _controllerConnector;};
    String getFullRemoteName();
    String getRemoteName();
    virtual String createCommand() = 0;
    virtual void executeCommand(String command) = 0;
    virtual String sendStateUpdate();
 };

 #endif
