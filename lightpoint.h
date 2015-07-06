/*
  LightPoint.h - Library for light point control.
  Created by Piotr Kaminski, 2015/07/05.
*/
#ifndef LightPoint_h
#define LightPoint_h

#include "Arduino.h"
#include "SiweckiSmartHome.h"

class LightPoint {
	private:
		int halogenButtonState;
		int lightPointState;
		int controlButtonPin;
		int controlOutputPin;
		String name;
 
	public:
		LightPoint(int controlButtonPin, int controlOutputPin, String name);
		void initialize();
		int checkControlButton();
		void setLightPointState(int state);
		String createCommand(int state);
};

#endif
