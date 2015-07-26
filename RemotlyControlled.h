#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

const String STATE_DELIMETER = "=";
const String LOCATION_DELIMETER = ".";

class RemotlyControlled {
  protected:
    String name;
    RemotlyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    String getNextRemotlyControlled(String command);
    String getSubCommand(String command);
    virtual String createCommand() = 0;
    virtual void executeCommand(String command) = 0;
    virtual void setParent(RemotlyControlled *_parent) {this->parent = _parent;} ;
    virtual String getRemoteName(){ return name;};
    virtual String sendStateUpdate();
 };

 #endif
