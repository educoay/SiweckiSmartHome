/*
 * Actor is a physical device dedicated to control home active objects. Those objects can be grouped
 * logically and usually are grouped in Rooms. Actor must be able to manage Rooms and dispatch command
 * sent by Controller to appropriate Room.
 *
 * Created by Piotr Kaminski, 2015/07/12.
 */


#ifndef Actor_h
#define Actor_h

#include "Arduino.h"

#include "ObjectRemotelyControlled.h"
#include "Point.h"
#include "Room.h"

/*
 *	Defines max number of Rooms which Actor can manage.
 */
#define ACTOR_MAX_ROOMS 20

class Actor: public ObjectRemotelyControlled {
  private:
    int rooms;
    
  protected:
    Room *roomsTable[ACTOR_MAX_ROOMS];
 
  public:

    /*
     * Public constructor to create anonymous actor. Actor name may be set during configuration set from
     * source.
     */
    Actor();

	/*
	 * Public constructor to create Actor. As parameter Actor name must be provided.
	 */
    Actor(const char* name);

    /*
     * Virtual desctructor to be able to correctly delete objects inheriting objects.
     */
    virtual ~Actor();

    /*
     * Add Room to be managed by this Actor. After this, Room will be part of three and will
     * be evaluated to perform commands.
     */
    void addRoom(Room* point);

    /**
     * Set connector for communication with controller. Set controller for all childs in object tree.
     */
    virtual void setControllerConnector(ControllerConnector* _controllerConnector);

    /*
     * Dispatch to all managed Rooms verification points in terms of control operation being in progress
     * (e.g. pressing hardware button, rising event). This method is called in infinitive loop to give
     * hardware infrastructure chance to rise event.
     */
    virtual void verifyControlPoints();

    /*
     * Initialize Actor. It is executed only on start up of system and called by setup() method in sketch.
     * Calls also initialize() method in each managed Room.
     */
    virtual void initialize();   

    /**
     * Creates command to set object to current state.
     *
     * @param 	command char array to store command. Please note that array must be long enough to store
     * 			command.
     *
     * NOTE: Current implementation does not allow to create command for entire Actor. It only return back
     * passed parameter.
     */
    virtual char* createCommand(char* command);

    /**
     * Creates command to set object to required state.
     *
     * @param 	command char array to store command. Please note that array must be long enough to store
     * 			command.
     *
     * NOTE: Current implementation does not allow to create command for entire Actor. It only return back
     * passed parameter.
     */
    virtual char* createCommand(int state, char* command);

    /**
     * Executes command on itself and/or all Rooms managed by Actor.
     * @param remoteName	Remote Name (effectively relative object address/location in objects tree) identifying
     * 						object to execute command against it.
     * @param command 		Command to be executed
     */
    virtual void executeCommand(const char* remoteName, const char* command);

    /**
     * Gets length/size of Full Remote Name of this object. Function used to determine size of buffer to
     * create
     */
    virtual int getFullRemoteNameSize();

    /**
     * Create Full Remote Name. Name will be copied into delivered and managed externally char table.
     * This method does not allocate any memory, it is up to developer to determine memory need by
     * getFullRemoteSize() function and allocate memory.
     *
     * @param fullRemoteName char table to copy into a Full Remote Name.
     */
    virtual char* getFullRemoteName(char* fullRemoteName);
};

#endif
