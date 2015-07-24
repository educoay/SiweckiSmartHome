/*
  Room.h - Class for collection of points to be controlled in single room.
  Created by Piotr Kaminski, 2015/07/12.
*/

#include "Arduino.h"
#include "Point.h"
#include "SiweckiSmartHome.h"

#ifndef Room_h
#define Room_h

#define ROOM_MAX_POINTS 20

class Room: public Command {
  private:
    int points;
    
  protected:
    String name;
    Point *pointsTable[ROOM_MAX_POINTS];
 
  public:
    Room(String name);
    ~Room();
    void addPoint(Point* point);
    virtual void initialize();
    virtual void verifyControlPoints();
    virtual String getObjectName();
    virtual String createCommand(int state);
    virtual String createCommand();
};

#endif
