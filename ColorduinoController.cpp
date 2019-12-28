#include "ColorduinoController.h"


void ColorduinoController_CMDPlayMode(CmdParser* parser)
{
	if (parser->equalCmdParam_P(1, PSTR("FREEMODE")))
	{
		Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::FreeMode"));
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
	}
	else if (parser->equalCmdParam_P(1, PSTR("PLASMA")))
	{
		if (parser->equalCmdParam_P(2, PSTR("COS")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::Plasma_Cos"));
			ColorduinoController::Instance()->PlayMode = Mode::Plasma_Cos;
		}
		else if (parser->equalCmdParam_P(2, PSTR("TAN")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::Plasma_Tan"));
			ColorduinoController::Instance()->PlayMode = Mode::Plasma_Tan;
		}
		else
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::Plasma_Sin"));
			ColorduinoController::Instance()->PlayMode = Mode::Plasma_Sin;
		}
	}
	else if (parser->equalCmdParam_P(1, PSTR("FADE")))
	{
		Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::Fade"));
		ColorduinoController::Instance()->PlayMode = Mode::Fade;
	}
	else if (parser->equalCmdParam_P(1, PSTR("LOADING")))
	{
		Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::Loading"));
		ColorduinoController::Instance()->PlayMode = Mode::Loading;
	}
	else if (parser->equalCmdParam_P(1, PSTR("SOLIDCOLOR")))
	{
		if (parser->equalCmdParam_P(2, PSTR("RED")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Red"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Red;
		}
		else if (parser->equalCmdParam_P(2, PSTR("GREEN")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Green"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Green;
		}
		else if (parser->equalCmdParam_P(2, PSTR("BLUE")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Blue"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Blue;
		}
		else if (parser->equalCmdParam_P(2, PSTR("YELLOW")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Yellow"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Yellow;
		}
		else if (parser->equalCmdParam_P(2, PSTR("PURPLE")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Purple"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Purple;
		}
		else if (parser->equalCmdParam_P(2, PSTR("CYAN")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Cyan"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Cyan;
		}
		else if (parser->equalCmdParam_P(2, PSTR("WHITE")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_White"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_White;
		}
		else if (parser->equalCmdParam_P(2, PSTR("AZUR")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Azur"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Azur;
		}
		else if (parser->equalCmdParam_P(2, PSTR("ORANGE")))
		{
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_Orange"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_Orange;
		}
		else
		{
			Serial.println(F("<<! CMDPlayMode: PlayMode not found"));
		}
	}
	else
	{
		Serial.println(F("<<! CMDPlayMode: PlayMode not found"));
	}
	
	ColorduinoController::Instance()->HaveToExitEvent = true;
}

void ColorduinoController_CMDSave(CmdParser* parser)
{
	EEPROMSaver eepromSaver;
	if (parser->equalCmdParam_P(1, PSTR("READ")))
	{
		Serial.println(F("<< CMDSave: Reading EEPROM"));
		eepromSaver.CheckEEPROMProfile();
	}
	else
	{
		Serial.println(F("<< CMDSave: Saving"));
		EEPROMProfile profile;
		profile.Setted_PlayMode = true;
		profile.PlayMode = ColorduinoController::Instance()->PlayMode;
		profile.Setted_IsMuted = true;
		profile.IsMuted = ColorduinoController::Instance()->Buzzer->Muted;
		eepromSaver.SaveEEPROMProfile(profile);
		Serial.println(F("<< CMDSave: Saved"));
	}
}

void ColorduinoController_CMDBeep(CmdParser* parser)
{
	if (parser->equalCmdParam_P(1, PSTR("MUTE")))
	{
		Serial.println(F("<< CMDBeep: MUTE"));
		ColorduinoController::Instance()->Buzzer->Muted = true;
	}
	else if (parser->equalCmdParam_P(1, PSTR("UNMUTE")))
	{
		Serial.println(F("<< CMDBeep: UNMUTE"));
		ColorduinoController::Instance()->Buzzer->Muted = false;
	}
	else if (parser->equalCmdParam_P(1, PSTR("CRITICAL")))
	{
		int i = atoi(parser->getCmdParam(2));
		Serial.print(F("<< CMDBeep: CRITICAL "));
		Serial.println(i);
		ColorduinoController::Instance()->Buzzer->BuzzerCriticalBeep(i);
	}
	else
	{
		int i = atoi(parser->getCmdParam(1));
		Serial.print(F("<< CMDBeep: "));
		Serial.println(i);
		ColorduinoController::Instance()->Buzzer->BuzzerBeep(i);
	}
}

void ColorduinoController_CMDStaticText(CmdParser* parser)
{
	if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
	{
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
		ColorduinoController::Instance()->HaveToExitEvent = true;
		Serial.println(F("<< CMDStaticText: PlayMode is now Mode::FreeMode"));
	}
	uint16_t Time = atoi(parser->getCmdParam(1));
	uint16_t Speed = atoi(parser->getCmdParam(2));
	char* Text = parser->getCmdParam(3);
	byte Red = byte(atoi(parser->getCmdParam(4)));
	byte Green = byte(atoi(parser->getCmdParam(5)));
	byte Blue = byte(atoi(parser->getCmdParam(6)));
	byte BackgroundRed = byte(atoi(parser->getCmdParam(7)));
	byte BackgroundGreen = byte(atoi(parser->getCmdParam(8)));
	byte BackgroundBlue = byte(atoi(parser->getCmdParam(9)));
	Serial.print(F("<< CMDStaticText {Time:")); Serial.print(Time);
	Serial.print(F("} {Speed:")); Serial.print(Speed);
	Serial.print(F("} {Text:")); Serial.print(Text);
	Serial.print(F("} {Red:")); Serial.print(Red);
	Serial.print(F("} {Green:")); Serial.print(Green);
	Serial.print(F("} {Blue:")); Serial.print(Blue);
	Serial.print(F("} [BackgroundRed:")); Serial.print(BackgroundRed);
	Serial.print(F("] [BackgroundGreen:")); Serial.print(BackgroundGreen);
	Serial.print(F("] [BackgroundBlue:")); Serial.print(BackgroundBlue);
	Serial.println(F("]"));
	ColorduinoController::Instance()->StaticText(Time, Speed, Text, Red, Green, Blue, BackgroundRed, BackgroundGreen, BackgroundBlue);
}

void ColorduinoController_CMDStaticText3x5(CmdParser* parser)
{
	if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
	{
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
		ColorduinoController::Instance()->HaveToExitEvent = true;
		Serial.println(F("<< CMDStaticText3x5: PlayMode is now Mode::FreeMode"));
	}
	char* Text = parser->getCmdParam(1);
	byte StartingScreen = byte(atoi(parser->getCmdParam(2)));
	byte x = byte(atoi(parser->getCmdParam(3)));
	byte y = byte(atoi(parser->getCmdParam(4)));
	byte Red = byte(atoi(parser->getCmdParam(5)));
	byte Green = byte(atoi(parser->getCmdParam(6)));
	byte Blue = byte(atoi(parser->getCmdParam(7)));
	Serial.print(F("<< CMDStaticText3x5 {Text:")); Serial.print(Text);
	Serial.print(F("} {StartingScreen:")); Serial.print(StartingScreen);
	Serial.print(F("} {x:")); Serial.print(x);
	Serial.print(F("} {y:")); Serial.print(y);
	Serial.print(F("} {Red:")); Serial.print(Red);
	Serial.print(F("} {Green:")); Serial.print(Green);
	Serial.print(F("} {Blue:")); Serial.print(Blue);
	Serial.println(F("}"));
	ColorduinoController::Instance()->StaticText3x5(Text, StartingScreen, x, y, Red, Green, Blue);
}

void ColorduinoController_CMDText(CmdParser* parser)
{
	if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
	{
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
		ColorduinoController::Instance()->HaveToExitEvent = true;
		Serial.println(F("<< CMDText: PlayMode is now Mode::FreeMode"));
	}
	uint16_t Time = atoi(parser->getCmdParam(1));
	uint16_t Speed = atoi(parser->getCmdParam(2));
	char* Text = parser->getCmdParam(3);
	byte Red = byte(atoi(parser->getCmdParam(4)));
	byte Green = byte(atoi(parser->getCmdParam(5)));
	byte Blue = byte(atoi(parser->getCmdParam(6)));
	byte BackgroundRed = byte(atoi(parser->getCmdParam(7)));
	byte BackgroundGreen = byte(atoi(parser->getCmdParam(8)));
	byte BackgroundBlue = byte(atoi(parser->getCmdParam(9)));
	Serial.print(F("<< CMDText {Time:")); Serial.print(Time);
	Serial.print(F("} {Speed:")); Serial.print(Speed);
	Serial.print(F("} {Text:")); Serial.print(Text);
	Serial.print(F("} {Red:")); Serial.print(Red);
	Serial.print(F("} {Green:")); Serial.print(Green);
	Serial.print(F("} {Blue:")); Serial.print(Blue);
	Serial.print(F("} [BackgroundRed:")); Serial.print(BackgroundRed);
	Serial.print(F("] [BackgroundGreen:")); Serial.print(BackgroundGreen);
	Serial.print(F("] [BackgroundBlue:")); Serial.print(BackgroundBlue);
	Serial.println(F("]"));
	ColorduinoController::Instance()->ScrollText(Time, Speed, Text, Red, Green, Blue, BackgroundRed, BackgroundGreen, BackgroundBlue);
}

void ColorduinoController_CMDIcon(CmdParser* parser)
{
	if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
	{
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
		ColorduinoController::Instance()->HaveToExitEvent = true;
		Serial.println(F("<< CMDIcon: PlayMode is now Mode::FreeMode"));
	}

	byte ScreenAddress = byte(atoi(parser->getCmdParam(1)));
	int16_t x = atoi(parser->getCmdParam(2));
	int16_t y = atoi(parser->getCmdParam(3));
	if (parser->equalCmdParam_P(4, PSTR("YOUTUBE")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageYoutube);
	}
	else if (parser->equalCmdParam_P(4, PSTR("TWITTER")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageTwitter);
	}
	else if(parser->equalCmdParam_P(4, PSTR("TWITCH")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageTwitch);
	}
	else if(parser->equalCmdParam_P(4, PSTR("HIGHTEMPERATURE")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageHighTemperature);
	}
	else if(parser->equalCmdParam_P(4, PSTR("AVERAGETEMPERATURE")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageAverageTemperature);
	}
	else if(parser->equalCmdParam_P(4, PSTR("LOWTEMPERATURE")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageLowTemperature);
	}
	else
	{
		Serial.println("<<! CMDIcon: Icon not found");
	}

	Serial.print(F("<< CMDIcon {ScreenAddress:")); Serial.print(ScreenAddress);
	Serial.print(F("} {x:")); Serial.print(x);
	Serial.print(F("} {y:")); Serial.print(y);
	Serial.print(F("} {Icon:")); Serial.print(parser->getCmdParam(4));
	Serial.println(F("}"));
}
//void ColorduinoController_CMDText(CmdParser* parser)
//{
//	Serial.println("<< CMDText");
//	ColorduinoController::Instance()->Buzzer->BuzzerBeep(atoi(parser->getCmdParam(1)));
//	if (parser->equalCmdParam_P(1, PSTR("ALARM")))
//	{
//		Serial.println(parser->getCmdParam(2));
//		ColorduinoController::Instance()->HaveToExitEvent = true;
//	}
//	else
//	{
//		Serial.println("<< CMDPlayMode:");
//	}
//}

void ColorduinoController_CMDHelp(CmdParser* parser)
{
	Serial.println(F("<< CMDHelp: {Needed Args:Format} [Optional Args:Format]"));
	Serial.println(F("<< CMDHelp: PLAYMODE [Mode:byte]"));
	Serial.println(F("<< CMDHelp:           Mode: 0 = Free, 1 = Plasma, 2 = Fade, 3 = Loading"));
	Serial.println(F("<< CMDHelp:           Mode: 10 = Solid Red, 11 = Solid Green, 12 = Solid Blue, 13 = Solid Yellow, 14 = Solid Purple, 15 = Solid Cyan, 16 = Solid White, 17 = Solid Azur, 18 = Solid Orange"));
	Serial.println(F("<< CMDHelp: SAVE"));
	Serial.println(F("<< CMDHelp: SAVE READ"));
	Serial.println(F("<< CMDHelp: BEEP {Frequency:uint}"));
	Serial.println(F("<< CMDHelp: BEEP MUTE"));
	Serial.println(F("<< CMDHelp: BEEP UNMUTE"));
	Serial.println(F("<< CMDHelp: BEEP CRITICAL {Time:uint}"));
	Serial.println(F("<< CMDHelp: STATICTEXT {Time:uint} {Speed:uint} {Text:char} {Red:byte} {Green:byte} {Blue:byte} [BackgroundRed:byte] [BackgroundGreen:byte] [BackgroundBlue:byte]"));
	Serial.println(F("<< CMDHelp: STATICTEXT3X5 {Text:char} {StartingScreen:byte} {x:byte} {y:byte} {Red:byte} {Green:byte} {Blue:byte}"));
	Serial.println(F("<< CMDHelp: TEXT {Time:uint} {Speed:uint} {Text:char} {Red:byte} {Green:byte} {Blue:byte} [BackgroundRed:byte] [BackgroundGreen:byte] [BackgroundBlue:byte]"));
	Serial.println(F("<< CMDHelp: ICON {ScreenAddress:byte} {x:byte} {y:byte} {Icon:enum}"));
	Serial.println(F("<< CMDHelp: PIXEL"));
}





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
	cmdCallback.addCmd(PSTR("BEEP"), &ColorduinoController_CMDBeep);
	cmdCallback.addCmd(PSTR("STATICTEXT"), &ColorduinoController_CMDStaticText);
	cmdCallback.addCmd(PSTR("STATICTEXT3X5"), &ColorduinoController_CMDStaticText3x5);
	cmdCallback.addCmd(PSTR("TEXT"), &ColorduinoController_CMDText);
	cmdCallback.addCmd(PSTR("ICON"), &ColorduinoController_CMDIcon);
	cmdCallback.addCmd(PSTR("PIXEL"), &ColorduinoController_CMDBeep);
	cmdCallback.addCmd(PSTR("HELP"), &ColorduinoController_CMDHelp);
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
	case Mode::Plasma_Sin:
		PlasmaAll(65535, 0);
		break;
	case Mode::Plasma_Cos:
		PlasmaAllCos(65535, 0);
		break;
	case Mode::Plasma_Tan:
		PlasmaAllTan(65535, 0);
		break;

	case Mode::Fade:
		ColorFader(65535);
		break;

	case Mode::Loading:
		Loading(1, 65535);
		break;

	case Mode::SolidColor_Red:
		FullColor(65535, 255, 0, 0);
		break;
	case Mode::SolidColor_Green:
		FullColor(65535, 0, 255, 0);
		break;
	case Mode::SolidColor_Blue:
		FullColor(65535, 0, 0, 255);
		break;
	case Mode::SolidColor_Yellow:
		FullColor(65535, 255, 255, 0);
		break;
	case Mode::SolidColor_Purple:
		FullColor(65535, 255, 0, 255);
		break;
	case Mode::SolidColor_Cyan:
		FullColor(65535, 0, 255, 255);
		break;
	case Mode::SolidColor_White:
		FullColor(65535, 255, 255, 255);
		break;
	case Mode::SolidColor_Azur:
		FullColor(65535, 46, 154, 255);
		break;
	case Mode::SolidColor_Orange:
		FullColor(65535, 255, 162, 46);
		break;

	default:
		while (!HaveToExitEvent)
		{
			CheckRoutine();
			SendToClient(DestI2CAddress1, 0);
			SendToClient(DestI2CAddress2, 1);
			SendToClient(DestI2CAddress3, 2);
			SendToClient(DestI2CAddress4, 3);
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

