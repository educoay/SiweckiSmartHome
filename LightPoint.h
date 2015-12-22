/*
  LightPoint.h - Class implementing light point control.
  Created by Piotr Kaminski, 2015/07/05.
*/

#include "Arduino.h"
#include "SiweckiSmartHome.h"
#include "Point.h"

#ifndef LightPoint_h
#define LightPoint_h

class LightPoint: public Point {
	private:
		int lightPointState;
		int controlButtonPin;
		int controlOutputPin;
    int buttonPreviousState;
    void setLightPointState(int state);
 
	public:
		LightPoint(int controlButtonPin, int controlOutputPin, String name);
    LightPoint(int controlButtonPin, int controlOutputPin, String name, ControllerConnector *controllerConnector);
    ~LightPoint();
		virtual void initialize();
		boolean isControlButtonPressed();
    void setLightPointOn();
    boolean isLightPointOn();
    void setLightPointOff();
    virtual void executeCommand(String queue, String command);
    virtual String createCommand();
    virtual String createCommand(int state);
    virtual String createQueue();
    virtual void verifyControlPoint();
};

#endif
