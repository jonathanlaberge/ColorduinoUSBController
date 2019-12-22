#include "EEPROMSaver.h"

EEPROMProfile EEPROMSaver::CheckEEPROMProfile()
{
	Serial.println(F("<< Setup: Check EEPROM"));
	EEPROMProfile profile;
	byte EEPROMbyte;
	EEPROM.get(0, EEPROMbyte);
	if (EEPROMbyte == 255)
	{
		EEPROM.get(1, EEPROMbyte);
		if (EEPROMbyte == 128)
		{
			EEPROM.get(2, EEPROMbyte);
			if (EEPROMbyte == 0)
			{
				Serial.println(F("<< Setup: Load config from EEPROM"));

				EEPROM.get(3, EEPROMbyte);
				Serial.print(F("<< Setup: Config: PlayMode = "));
				Serial.println(EEPROMbyte);
				profile.PlayMode = EEPROMbyte;

				EEPROM.get(4, EEPROMbyte);
				Serial.print(F("<< Setup: Config: IsMuted = "));
				Serial.println(EEPROMbyte);
				profile.IsMuted = EEPROMbyte;
			}
		}
	}
	return profile;
}

void EEPROMSaver::SaveEEPROMProfile(EEPROMProfile profile)
{
	Serial.println(F("<< Setup: Saving EEPROM..."));
	EEPROM.update( 0, 255);
	EEPROM.update( 1, 128);
	EEPROM.update( 2, 0);

	if (profile.Setted_PlayMode)
	{
		EEPROM.update( 3, profile.PlayMode);
		Serial.print(F("<< Setup: Config: PlayMode = "));
		Serial.println(profile.PlayMode);
	}
	if (profile.Setted_IsMuted)
	{
		EEPROM.update( 4, profile.IsMuted);
		Serial.print(F("<< Setup: Config: IsMuted = "));
		Serial.println(profile.IsMuted);
	}
}
