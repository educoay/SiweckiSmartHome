#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

/**
 * Any point or object that can be remotely controlled. Remote control means that object
 * can accept commands send by server or device different than Arduino board when program 
 * resists.  
 */
class ObjectRemotlyControlled {
  protected:
    String name;
    ObjectRemotlyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    ObjectRemotlyControlled(String _name) { this->name = _name;};
    String getNextRemotlyControlled(String queue);
    String getSubRemotlyControlled(String queue);
    void setParent(ObjectRemotlyControlled *_parent) {this->parent = _parent;} ;
    void setControllerConnector(ControllerConnector *_controllerConnector) {this->controllerConnector = _controllerConnector;};
    void sendStateUpdate();

    /**
     * Get name of object. Only local name will be returned without location in hierarchy.
     */
    String getRemoteName();

    /**
     * Get full name of object including location in hierarchy. Name is created using
     * Unix like directory structure where delimiter '/' is used to separate objects.
     *
     * E.g. /Ard0/Room/Point
     */
    virtual String getFullRemoteName();

    /**
     * Create command which describes current state of object.
     * E.g. In case of (@ref LightPoint) this will create command to set light in On/Off position
     * depending on current state.
     */
    virtual String createCommand() = 0;

    /**
     * Create comment to set required state of object.
     * E.g. If there is a need to set (@ref LightPoint) into On state, appropriate parameter should
     * be provided.
     */
    virtual String createCommand(int state) = 0;

    virtual void executeCommand(String queue, String command) = 0;
 };

 #endif
