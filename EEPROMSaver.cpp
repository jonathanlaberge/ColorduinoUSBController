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
				profile.PlayMode = static_cast<Mode>(EEPROMbyte);
				profile.Setted_PlayMode = true;

				EEPROM.get(4, EEPROMbyte);
				Serial.print(F("<< Setup: Config: IsMuted = "));
				Serial.println(EEPROMbyte);
				profile.IsMuted = EEPROMbyte;
				profile.Setted_IsMuted = true;

				EEPROM.get(5, EEPROMbyte);
				Serial.print(F("<< Setup: Config: WaitForConsole = "));
				Serial.println(EEPROMbyte);
				profile.WaitForConsole = EEPROMbyte;
				profile.Setted_WaitForConsole = true;
				if (profile.WaitForConsole && profile.PlayMode != Mode::FreeMode)
				{
					Serial.println(F("<<! Setup: Config: PlayMode must be set to Mode::FreeMode"));
					profile.PlayMode = Mode::FreeMode;
				}

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
		EEPROM.update(4, profile.IsMuted);
		Serial.print(F("<< Setup: Config: IsMuted = "));
		Serial.println(profile.IsMuted);
	}
	if (profile.Setted_WaitForConsole)
	{
		EEPROM.update(5, profile.WaitForConsole);
		Serial.print(F("<< Setup: Config: WaitForConsole = "));
		Serial.println(profile.WaitForConsole);
	}
}
