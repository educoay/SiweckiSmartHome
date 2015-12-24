/*
  Room.h - Defines physical or virtual room for collection of points to be controlled.

  Created by Piotr Kaminski, 2015/07/12.
*/

#include "Point.h"
#include "SiweckiSmartHome.h"

#ifndef Room_h
#define Room_h

#define ROOM_MAX_POINTS 20

class Room: public ObjectRemotelyControlled {
  private:
    int points;
    
  protected:
    Point *pointsTable[ROOM_MAX_POINTS];
 
  public:
    Room(String name);
    virtual ~Room();
    void addPoint(Point* point);
    virtual void initialize();
    virtual void verifyControlPoints();
    virtual String createCommand();
    virtual String createCommand(int state);
    virtual void executeCommand(String objectFullRemoteName, String command);
};

#endif
