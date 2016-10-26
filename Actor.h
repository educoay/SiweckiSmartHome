/*
  Actor.h - Class for collection of points to be controlled in single room.
  Created by Piotr Kaminski, 2015/07/12.
*/


#ifndef Actor_h
#define Actor_h

#include "Arduino.h"

#include "ObjectRemotelyControlled.h"
#include "Point.h"
#include "Room.h"

#define ACTOR_MAX_ROOMS 20

class Actor: public ObjectRemotelyControlled {
  private:
    int rooms;
    
  protected:
    Room *roomsTable[ACTOR_MAX_ROOMS];
 
  public:
    Actor(const char* name);
    virtual ~Actor();
    void addRoom(Room* point);
    virtual void verifyControlPoints();
    virtual void initialize();   
    virtual char* createCommand(char* command);
    virtual char* createCommand(int state, char* command);
    virtual void executeCommand(const char* queue, const char* command);
    virtual int getFullRemoteNameSize();
    virtual char* getFullRemoteName(char* fullRemoteName);
};

#endif
