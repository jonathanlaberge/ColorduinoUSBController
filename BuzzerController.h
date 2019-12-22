#ifndef hBuzzerController
#define hBuzzerController

#include "Arduino.h"
#include <avr/wdt.h>

class BuzzerController
{
public:
	BuzzerController();
	bool Muted;
	void BuzzerCriticalBeep(int time);
	void BuzzerBeep(int hz);
};

#endif
