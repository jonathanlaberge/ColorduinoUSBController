#ifndef hEEPROMSaver
#define hEEPROMSaver
#include "Arduino.h"
#include <EEPROM.h>
#include "EEPROMProfile.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

class EEPROMSaver
{
public:
	EEPROMProfile CheckEEPROMProfile();
	void SaveEEPROMProfile(EEPROMProfile profile);
};

#endif
