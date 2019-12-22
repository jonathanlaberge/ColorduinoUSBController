#include "BuzzerController.h"
#include "Config.h"

BuzzerController::BuzzerController()
{
	pinMode(Config_Pin_Beeper, OUTPUT);
	Muted = false;
}

void BuzzerController::BuzzerCriticalBeep(int time)
{
	if (Muted) return;
	for (int i = 0; i < time; i++)
	{
		tone(Config_Pin_Beeper, 512);
		delay(500);
		tone(Config_Pin_Beeper, 2000);
		delay(500);
		wdt_reset();
	}
	noTone(Config_Pin_Beeper);
}

void BuzzerController::BuzzerBeep(int hz)
{
	if (Muted) return;
	tone(Config_Pin_Beeper, hz);
	delay(100);
	noTone(Config_Pin_Beeper);
}
