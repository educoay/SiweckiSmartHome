/*
  LightPoint.h - Class implementing light point control.
  Created by Piotr Kaminski, 2015/07/05.
*/

#ifndef LightPoint_h
#define LightPoint_h

#include "Arduino.h"
#include "SiweckiSmartHome.h"
#include "Point.h"

class LightPoint: public Point {
	private:
		int lightPointState;
		int controlButtonPin;
		int controlOutputPin;
		int buttonPreviousState;
		void setLightPointState(int state);
 
	public:
		LightPoint(int controlButtonPin, int controlOutputPin, const char* name);
		LightPoint(int controlButtonPin, int controlOutputPin, const char* name, ControllerConnector *controllerConnector);
		virtual ~LightPoint();
		virtual void initialize();
		boolean isControlButtonPressed();
		void setLightPointOn();
		boolean isLightPointOn();
		void setLightPointOff();
		virtual void executeCommand(const char* remoteName, const char* command);
		virtual char* createCommand(char* command);
		virtual char* createCommand(int state,  char* command);
		virtual void verifyControlPoint();
};

#endif
