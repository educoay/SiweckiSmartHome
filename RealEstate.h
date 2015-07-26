/*
  RealEstate.h - Class for collection of points to be controlled in single room.
  Created by Piotr Kaminski, 2015/07/12.
*/


#ifndef RealEstate_h
#define RealEstate_h

#include "Arduino.h"
#include "Point.h"
#include "Room.h"
#include "RemotlyControlled.h"

#define REALESTATE_MAX_POINTS 20

class RealEstate: public RemotlyControlled {
  private:
    int rooms;
    
  protected:
    String name;
    Room *roomsTable[REALESTATE_MAX_POINTS];
 
  public:
    RealEstate(String name);
    ~RealEstate();
    void addRoom(Room* point);
    virtual void verifyControlPoints();
    virtual void initialize();
    virtual String getRemoteName();    
    virtual String createCommand();
    virtual void executeCommand(String estateCommand);
};

#endif
