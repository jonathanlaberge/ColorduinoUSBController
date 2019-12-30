#include "BuzzerController.h"
#include "ColorduinoController.h"
#include <avr/wdt.h>

void setup()
{
	ColorduinoController::Instance()->Buzzer->BuzzerBeep(500);
	Serial.begin(Config_Serial_Speed);
	Serial.println(F("<< Setup"));
	ColorduinoController::Instance()->Setup();
	ColorduinoController::Instance()->Buzzer->BuzzerBeep(1000);
}

void loop()
{
	ColorduinoController::Instance()->Loop();
	wdt_reset();
}
