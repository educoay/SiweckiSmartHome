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
		int lightPointState = 0;
		int controlButtonPin = 0;
		int controlOutputPin = 0;
		int buttonPreviousState = 0;
		void setLightPointState(int state);
 
	public:
		LightPoint(int controlButtonPin, int controlOutputPin, String name);
    LightPoint(int controlButtonPin, int controlOutputPin, String name, ControllerConnector *controllerConnector);
    virtual ~LightPoint();
		virtual void initialize();
		boolean isControlButtonPressed();
    void setLightPointOn();
    boolean isLightPointOn();
    void setLightPointOff();
    virtual void executeCommand(String objectFullRemoteName, String command);
    virtual String createCommand();
    virtual String createCommand(int state);
    virtual void verifyControlPoint();
};

#endif
