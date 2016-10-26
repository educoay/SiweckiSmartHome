/*
  Room.h - Defines physical or virtual room for collection of points to be controlled.

  Created by Piotr Kaminski, 2015/07/12.
*/

#ifndef Room_h
#define Room_h

#include "Point.h"
#include "SiweckiSmartHome.h"

#define ROOM_MAX_POINTS 20

class Room: public ObjectRemotelyControlled {
  private:
    int points;
    
  protected:
    Point *pointsTable[ROOM_MAX_POINTS];
 
  public:
    Room(const char* name);
    virtual ~Room();
    void addPoint(Point* point);
    virtual void initialize();
    virtual void verifyControlPoints();
    virtual char* createCommand(char* command);
    virtual char* createCommand(int state, char* command);
    virtual void executeCommand(const char* objectFullRemoteName, const char* command);
};

#endif
