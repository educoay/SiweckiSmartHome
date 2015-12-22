/*
  LightPoint.h - Class for any point that can be controlled.
  Created by Piotr Kaminski, 2015/07/12.

*/

#ifndef Point_h
#define Point_h

#include "ObjectRemotlyControlled.h"

class Point: public ObjectRemotlyControlled {
 
  public:
    Point(String name):ObjectRemotlyControlled(name){};
    ~Point(){};
    virtual void initialize() = 0;
    virtual boolean isControlButtonPressed() = 0;
    virtual void verifyControlPoint() = 0;
};

#endif
