#include "ColorduinoController.h"


void ColorduinoController_CMDPlayMode(CmdParser* parser)
{
	
	ColorduinoController::Instance()->PlayMode = byte(atoi(parser->getCmdParam(1)));
		
	Serial.print("<< ColorduinoController_CMDPlayMode: PlayMode is now ");
	Serial.println(ColorduinoController::Instance()->PlayMode);
	ColorduinoController::Instance()->HaveToExitEvent = true;
}

void ColorduinoController_CMDSave(CmdParser* parser)
{
	Serial.println("<< ColorduinoController_CMDSave: Saving");
	EEPROMSaver eepromSaver;
	EEPROMProfile profile;
	profile.Setted_PlayMode = true;
	profile.PlayMode = ColorduinoController::Instance()->PlayMode;
	profile.Setted_IsMuted = true;
	profile.IsMuted = ColorduinoController::Instance()->Buzzer->Muted;
	eepromSaver.SaveEEPROMProfile(profile);
	Serial.println("<< ColorduinoController_CMDSave: Saved");
}

//void ColorduinoController_CMDText(CmdParser* parser)
//{
//	Serial.println("<< ColorduinoController_CMDPlayMode:");
//	if (parser->equalCmdParam_P(1, PSTR("ALARM")))
//	{
//		Serial.println(parser->getCmdParam(2));
//		ColorduinoController::Instance()->HaveToExitEvent = true;
//	}
//	else
//	{
//		Serial.println("<< ColorduinoController_CMDPlayMode:");
//	}
//}






ColorduinoController::ColorduinoController()
{
	Buzzer = new BuzzerController();
}

ColorduinoController* ColorduinoController::instance = 0;

ColorduinoController* ColorduinoController::Instance()
{
	if (instance == 0)
	{
		instance = new ColorduinoController();
	}

	return instance;
}

void ColorduinoController::Setup()
{
#ifdef Enable_WireTransmission
	Serial.println(F("<< Setup: Configure Wire"));
	Wire.begin(1);
#endif

	Serial.println(F("<< Setup: Variables"));

	EEPROMSaver eepromSaver;
	EEPROMProfile profile = eepromSaver.CheckEEPROMProfile();
	PlayMode = profile.PlayMode;
	Buzzer->Muted = profile.IsMuted;

	cmdCallback.addCmd(PSTR("PLAYMODE"), &ColorduinoController_CMDPlayMode);
	cmdCallback.addCmd(PSTR("SAVE"), &ColorduinoController_CMDSave);
	cmdBuffer.setEcho(true);

	pinMode(LED_BUILTIN, OUTPUT);

	CleanUpPixel(0);
	CleanUpPixel(1);
	CleanUpPixel(2);
	CleanUpPixel(3);

	SendToClient(DestI2CAddress1, 0);
	SendToClient(DestI2CAddress2, 1);
	SendToClient(DestI2CAddress3, 2);
	SendToClient(DestI2CAddress4, 3);
}

void ColorduinoController::Loop()
{
	FullCheckRoutine();

	switch (PlayMode)
	{
	case 1:
		PlasmaAll(65535, 0);
		break;
	case 2:
		ColorFader(65535);
		break;
	default:
		while (!HaveToExitEvent)
		{
			CheckRoutine();
		}
		break;
	}
	
	CleanUpPixel(0);
	CleanUpPixel(1);
	CleanUpPixel(2);
	CleanUpPixel(3);
		
	SendToClient(DestI2CAddress1, 0);
	SendToClient(DestI2CAddress2, 1);
	SendToClient(DestI2CAddress3, 2);
	SendToClient(DestI2CAddress4, 3);
}

void ColorduinoController::SetLanguageString(byte index)
{
	strcpy_P(languageString, (char*)pgm_read_word(&string_table[index]));
}

void ColorduinoController::CheckRoutine()
{
	wdt_reset();
	cmdCallback.updateCmdProcessing(&cmdParser, &cmdBuffer, &Serial);
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void ColorduinoController::FullCheckRoutine()
{
	HaveToExitEvent = false;
	wdt_reset();
}

