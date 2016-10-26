#ifndef RemotlyControlled_h
#define RemotlyControlled_h

#include "Arduino.h"
#include "ControllerConnector.h"

/**
 * Any point or object that can be remotely controlled. Remote control means that object
 * can accept commands send by server or device different than Arduino board when program 
 * resists.  
 * 
 * Any remotely controlled object needs to have a name to be identified.
 */
class ObjectRemotelyControlled {

  protected:
    char* name;
    ObjectRemotelyControlled *parent = NULL;
    ControllerConnector *controllerConnector = NULL;
    
  public:
    /**
     * Constructor to force giving a name to controlled objects.
     */
    ObjectRemotelyControlled(const char* _name) { this->name = strdup(_name);};
    
    /**p
     * Virtual destructor to allow clean up for any children of this object.
     */
    virtual ~ObjectRemotelyControlled() { delete this->name;};

    /**
     * Set parent object to create hierarchy
     */
    void setParent(ObjectRemotelyControlled *_parent) {this->parent = _parent;} ;

    /**
     * Set connector for communication with controller.
     */
    void setControllerConnector(ControllerConnector *_controllerConnector) {this->controllerConnector = _controllerConnector;};

    /**
     * Gets name of top object in hierarchy described by full remote name.
     *
     * E.g.: for /Adr0/Room1/Point1 will result with Ard0
     *
     * @param objectFullRemoteName pointer to source string.
     * @param topHierarchyName pointer to table where name should be stored.
     */
    char* getTopHierarchyName(const char* objectFullRemoteName, char* topHierarchyName);

    /**
     * Gets pointer to location of object with subtraction of top object in hierarchy described by full remote name.
     * It reused parameter string and returns pointer to substring from parameter.
     *
     * E.g.: for /Adr0/Room1/Point1 will result with /Room1/Point1
     */
    char* getSublocation(const char* objectFullRemoteName);

    /**
     * Send update of current state to Controller
     */
    void sendStateUpdate();

    /**
     * Get name of object. Only local name will be returned without location in hierarchy.
     */
    virtual char* getRemoteName();

    /**
     * Get full name of object including location in hierarchy. Name is created using
     * Unix like directory structure where delimiter '/' is used to separate objects.
     *
     * E.g. /Ard0/Room/Point
     *
     * @param getFullRemoteName Char table to copy into full remote name.
     * @return Table where remote name was copied in.
     */
    virtual char* getFullRemoteName(char* fullRemoteName);

    /**
     * Size (length) of full remote name, including names of parent and delimeters.
     *
     * @return Full remote name size.
     */
    virtual int getFullRemoteNameSize();

    /**
     * Create command which describes current state of object.
     * E.g. In case of {@link LightPoint} this will create command to set light in On/Off position
     * depending on current state.
     *
     * @param command Pointer to table where command string should be copied in.
     */
    virtual char* createCommand(char* command) = 0;

    /**
     * Create comment to set required state of object.
     * E.g. If there is a need to set {@link LightPoint} into On state, appropriate parameter should
     * be provided.
     *
     * @param command Pointer to table where command string should be copied in.
     */
    virtual char* createCommand(int state, char* command) = 0;

    /**
     * Execution of command on object. Function responsible to verify given object is object which should
     * respond to command (by object full name) and perform execution.
     */
    virtual void executeCommand(const char* objectFullRemoteName, const char* command) = 0;
 };

 #endif
