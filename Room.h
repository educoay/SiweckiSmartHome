/*
  Room.h - Defines physical or virtual room for collection of points to be controlled.

  Created by Piotr Kaminski, 2015/07/12.
*/

#include "Point.h"
#include "SiweckiSmartHome.h"

#ifndef Room_h
#define Room_h

#define ROOM_MAX_POINTS 20

class Room: public ObjectRemotlyControlled {
  private:
    int points;
    
  protected:
    Point *pointsTable[ROOM_MAX_POINTS];
 
  public:
    Room(String name);
    ~Room();
    void addPoint(Point* point);
    virtual void initialize();
    virtual void verifyControlPoints();
    virtual String createCommand();
    virtual String createQueue();
    virtual void executeCommand(String queue, String command);
};

#endif
