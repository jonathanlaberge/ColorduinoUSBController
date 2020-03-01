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
			Serial.println(F("<< CMDPlayMode: PlayMode is now Mode::SolidColor_White"));
			ColorduinoController::Instance()->PlayMode = Mode::SolidColor_White;
		}
	}
	else
	{
		int i = atoi(parser->getCmdParam(1));
		Serial.print(F("<< CMDPlayMode: PlayMode is now "));
		Serial.println(i);
		ColorduinoController::Instance()->PlayMode = static_cast<Mode>(i);
	}

	if (ColorduinoController::Instance()->WaitForConsole)
	{
		Serial.println(F("<<! CMDPlayMode: Setting for WaitForConsole has been set automatically to false"));
		ColorduinoController::Instance()->WaitForConsole = false;
	}
	
	ColorduinoController::Instance()->HaveToExitEvent = true;
}

void ColorduinoController_CMDSave(CmdParser* parser)
{
	EEPROMSaver eepromSaver;
	EEPROMProfile profile;
	if (parser->equalCmdParam_P(1, PSTR("READ")))
	{
		Serial.println(F("<< CMDSave: Reading EEPROM"));
		profile = eepromSaver.CheckEEPROMProfile();
		ColorduinoController::Instance()->PlayMode = profile.PlayMode;
		ColorduinoController::Instance()->Buzzer->Muted = profile.IsMuted;
		ColorduinoController::Instance()->WaitForConsole = profile.WaitForConsole;
	}
	else
	{
		Serial.println(F("<< CMDSave: Saving"));

		profile.Setted_PlayMode = true;
		profile.PlayMode = ColorduinoController::Instance()->PlayMode;

		profile.Setted_IsMuted = true;
		profile.IsMuted = ColorduinoController::Instance()->Buzzer->Muted;

		profile.Setted_WaitForConsole = true;
		profile.WaitForConsole = ColorduinoController::Instance()->WaitForConsole;

		profile.Setted_WaitForSending = true;
		profile.WaitForSending = ColorduinoController::Instance()->WaitForSending;

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
	else if (parser->equalCmdParam_P(4, PSTR("LOWTEMPERATURE")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageLowTemperature);
	}
	else if (parser->equalCmdParam_P(4, PSTR("CPU")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageCPU);
	}
	else if (parser->equalCmdParam_P(4, PSTR("RAM")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageRAM);
	}
	else if (parser->equalCmdParam_P(4, PSTR("MAIL")))
	{
		ColorduinoController::Instance()->DrawImage8x8(ScreenAddress, x, y, ImageMail);
	}
	else
	{
		Serial.println(F("<<! CMDIcon: Icon not found"));
	}

	Serial.print(F("<< CMDIcon {ScreenAddress:")); Serial.print(ScreenAddress);
	Serial.print(F("} {x:")); Serial.print(x);
	Serial.print(F("} {y:")); Serial.print(y);
	Serial.print(F("} {Icon:")); Serial.print(parser->getCmdParam(4));
	Serial.println(F("}"));
}

void ColorduinoController_CMDPixel(CmdParser* parser)
{
	if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
	{
		ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
		ColorduinoController::Instance()->HaveToExitEvent = true;
		Serial.println(F("<< CMDPixel: PlayMode is now Mode::FreeMode"));
	}
	byte ScreenAddress = byte(atoi(parser->getCmdParam(1)));
	byte x = byte(atoi(parser->getCmdParam(2)));
	byte y = byte(atoi(parser->getCmdParam(3)));
	byte w = byte(atoi(parser->getCmdParam(4)));
	byte h = byte(atoi(parser->getCmdParam(5)));
	byte Red = byte(atoi(parser->getCmdParam(6)));
	byte Green = byte(atoi(parser->getCmdParam(7)));
	byte Blue = byte(atoi(parser->getCmdParam(8)));
	Serial.print(F("<< CMDPixel {ScreenAddress:")); Serial.print(ScreenAddress);
	Serial.print(F("} {x:")); Serial.print(x);
	Serial.print(F("} {y:")); Serial.print(y);
	Serial.print(F("} {w:")); Serial.print(w);
	Serial.print(F("} {h:")); Serial.print(h);
	Serial.print(F("} {Red:")); Serial.print(Red);
	Serial.print(F("} {Green:")); Serial.print(Green);
	Serial.print(F("} {Blue:")); Serial.print(Blue);
	Serial.println(F("}"));
	ColorduinoController::Instance()->SetPixelArea(ScreenAddress, x, y, w, h, Red, Green, Blue);
}

void ColorduinoController_CMDClear(CmdParser* parser)
{
	ColorduinoController::Instance()->Buzzer->BuzzerBeep(atoi(parser->getCmdParam(1)));
	if (parser->equalCmdParam_P(1, PSTR("1")) || parser->equalCmdParam_P(2, PSTR("1")) || parser->equalCmdParam_P(3, PSTR("1")))
	{
		Serial.println(F("<< CMDClear: Clearing screen 0"));
		ColorduinoController::Instance()->CleanUpPixel(0);
	}
	else if (parser->equalCmdParam_P(1, PSTR("2")) || parser->equalCmdParam_P(2, PSTR("2")) || parser->equalCmdParam_P(3, PSTR("2")))
	{
		Serial.println(F("<< CMDClear: Clearing screen 1"));
		ColorduinoController::Instance()->CleanUpPixel(1);
	}
	else if (parser->equalCmdParam_P(1, PSTR("3")) || parser->equalCmdParam_P(2, PSTR("3")) || parser->equalCmdParam_P(3, PSTR("3")))
	{
		Serial.println(F("<< CMDClear: Clearing screen 2"));
		ColorduinoController::Instance()->CleanUpPixel(2);
	}
	else if (parser->equalCmdParam_P(1, PSTR("4")) || parser->equalCmdParam_P(2, PSTR("4")) || parser->equalCmdParam_P(3, PSTR("4")))
	{
		Serial.println(F("<< CMDClear: Clearing screen 3"));
		ColorduinoController::Instance()->CleanUpPixel(3);
	}
	else
	{
		Serial.println(F("<< CMDClear: Clearing all screen"));
		ColorduinoController::Instance()->CleanUpPixel(0);
		ColorduinoController::Instance()->CleanUpPixel(1);
		ColorduinoController::Instance()->CleanUpPixel(2);
		ColorduinoController::Instance()->CleanUpPixel(3);
	}
}

void ColorduinoController_CMDSend(CmdParser* parser)
{
	bool sent = false;
	ColorduinoController::Instance()->Buzzer->BuzzerBeep(atoi(parser->getCmdParam(1)));
	if (parser->equalCmdParam_P(1, PSTR("1")) || parser->equalCmdParam_P(2, PSTR("1")) || parser->equalCmdParam_P(3, PSTR("1")))
	{
		sent = true;
		Serial.println(F("<< CMDSend: Sending screen 0"));
		ColorduinoController::Instance()->SendToClient(DestI2CAddress1, 0);
	}
	if (parser->equalCmdParam_P(1, PSTR("2")) || parser->equalCmdParam_P(2, PSTR("2")) || parser->equalCmdParam_P(3, PSTR("2")))
	{
		sent = true;
		Serial.println(F("<< CMDSend: Sending screen 1"));
		ColorduinoController::Instance()->SendToClient(DestI2CAddress2, 1);
	}
	if (parser->equalCmdParam_P(1, PSTR("3")) || parser->equalCmdParam_P(2, PSTR("3")) || parser->equalCmdParam_P(3, PSTR("3")))
	{
		sent = true;
		Serial.println(F("<< CMDSend: Sending screen 2"));
		ColorduinoController::Instance()->SendToClient(DestI2CAddress3, 2);
	}
	if (parser->equalCmdParam_P(1, PSTR("4")) || parser->equalCmdParam_P(2, PSTR("4")) || parser->equalCmdParam_P(3, PSTR("4")))
	{
		sent = true;
		Serial.println(F("<< CMDSend: Sending screen 3"));
		ColorduinoController::Instance()->SendToClient(DestI2CAddress4, 3);
	}
	if (!sent)
	{
		Serial.println(F("<< CMDSend: Sending all screen"));
		ColorduinoController::Instance()->SendToClient(DestI2CAddress1, 0);
		ColorduinoController::Instance()->SendToClient(DestI2CAddress2, 1);
		ColorduinoController::Instance()->SendToClient(DestI2CAddress3, 2);
		ColorduinoController::Instance()->SendToClient(DestI2CAddress4, 3);
	}
}

void ColorduinoController_CMDSetting(CmdParser* parser)
{
	if (parser->equalCmdParam_P(1, PSTR("WATCHDOG")))
	{
		if (parser->equalCmdParam_P(2, PSTR("1")))
		{
			Serial.println(F("<< CMDSetting: WatchDog enabled to 1s"));
			wdt_enable(WDTO_1S);
		}
		else if (parser->equalCmdParam_P(2, PSTR("2")))
		{
			Serial.println(F("<< CMDSetting: WatchDog enabled to 2s"));
			wdt_enable(WDTO_2S);
		}
		else if (parser->equalCmdParam_P(2, PSTR("4")))
		{
			Serial.println(F("<< CMDSetting: WatchDog enabled to 4s"));
			wdt_enable(WDTO_4S);
		}
		else if (parser->equalCmdParam_P(2, PSTR("8")))
		{
			Serial.println(F("<< CMDSetting: WatchDog enabled to 8s"));
			wdt_enable(WDTO_8S);
		}
		else
		{
			Serial.println(F("<< CMDSetting: WatchDog disabled"));
			wdt_disable();
		}
	}
	else if (parser->equalCmdParam_P(1, PSTR("WAITFORCONSOLE")))
	{
		if (parser->equalCmdParam_P(2, PSTR("TRUE")))
		{
			Serial.println(F("<< CMDSetting: WaitForConsole set to true"));
			Serial.println(F("<<! CMDSetting: Make sure that the WatchDog is disabled"));
			if (ColorduinoController::Instance()->PlayMode != Mode::FreeMode)
			{
				ColorduinoController::Instance()->PlayMode = Mode::FreeMode;
				ColorduinoController::Instance()->HaveToExitEvent = true;
				Serial.println(F("<< CMDSetting: PlayMode is now Mode::FreeMode"));
			}
			ColorduinoController::Instance()->WaitForConsole = true;
		}
		else
		{
			Serial.println(F("<< CMDSetting: WaitForConsole set to false"));
			ColorduinoController::Instance()->WaitForConsole = false;
		}
	}
	else if (parser->equalCmdParam_P(1, PSTR("WAITFORSENDING")))
	{
		if (parser->equalCmdParam_P(2, PSTR("TRUE")))
		{
			Serial.println(F("<< CMDSetting: WaitForSending set to true"));
			ColorduinoController::Instance()->WaitForSending = true;
		}
		else
		{
			Serial.println(F("<< CMDSetting: WaitForSending set to false"));
			ColorduinoController::Instance()->WaitForSending = false;
		}
	}
	else if (parser->equalCmdParam_P(1, PSTR("ECHOCONSOLE")))
	{
		if (parser->equalCmdParam_P(2, PSTR("FALSE")))
		{
			Serial.println(F("<< CMDSetting: EchoConsole set to false"));
			ColorduinoController::Instance()->SetConsoleEcho(false);
		}
		else
		{
			Serial.println(F("<< CMDSetting: EchoConsole set to true"));
			ColorduinoController::Instance()->SetConsoleEcho(true);
		}
	}
	else
	{
		Serial.println(F("<<! CMDSetting: Unknow setting"));
		wdt_disable();
	}
}

void ColorduinoController_CMDMemFree(CmdParser* parser)
{
	Serial.print(F("<< CMDMemFree: "));
	Serial.println(FreeMemory());
}

void ColorduinoController_CMDHelp(CmdParser* parser)
{
	Serial.println(F("<< CMDHelp: {Needed Args:Format} [Optional Args:Format] (Possible Action) (<Default Action>)"));
	Serial.println(F("<< CMDHelp:		Note: ScreenAddress start at 0 and end at 3. ScreenAddressAtOne start to 1 and end at 4."));
	Serial.println(F("<< CMDHelp: PLAYMODE [Mode:byte]"));
	Serial.println(F("<< CMDHelp: PLAYMODE (FREEMODE, PLASMA (<SIN>, COS, TAN), FADE, LOADING, SOLIDCOLOR (RED, GREEN, BLUE, YELLOW, PURPLE, CYAN, <WHITE>, AZUR, ORANGE)"));
	Serial.println(F("<< CMDHelp: SAVE (READ)"));
	Serial.println(F("<< CMDHelp: BEEP ({Frequency:uint}, MUTE, UNMUTE, CRITICAL {Time:uint})"));
	Serial.println(F("<< CMDHelp: STATICTEXT {Time:uint} {Speed:uint} {Text:char} {Red:byte} {Green:byte} {Blue:byte} [BackgroundRed:byte] [BackgroundGreen:byte] [BackgroundBlue:byte]"));
	Serial.println(F("<< CMDHelp: STATICTEXT3X5 {Text:char} {StartingScreen:byte} {x:byte} {y:byte} {Red:byte} {Green:byte} {Blue:byte}"));
	Serial.println(F("<< CMDHelp: TEXT {Time:uint} {Speed:uint} {Text:char} {Red:byte} {Green:byte} {Blue:byte} [BackgroundRed:byte] [BackgroundGreen:byte] [BackgroundBlue:byte]"));
	Serial.println(F("<< CMDHelp: ICON {ScreenAddress:byte} {x:byte} {y:byte} {Icon:enum}"));
	Serial.println(F("<< CMDHelp: PIXEL {ScreenAddress:byte} {x:byte} {y:byte} {w:byte} {h:byte} {Red:byte} {Green:byte} {Blue:byte}"));
	Serial.println(F("<< CMDHelp: CLEAR ([ScreenAddressAtOne:byte], [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte], [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte], ALL)"));
	Serial.println(F("<< CMDHelp: SEND ([ScreenAddressAtOne:byte], [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte], [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte] [ScreenAddressAtOne:byte], ALL)"));
	Serial.println(F("<< CMDHelp: SETTING (WAITFORCONSOLE (TRUE, <FALSE>), WAITFORSENDING (TRUE, <FALSE>), ECHOCONSOLE (<TRUE>, FALSE), WATCHDOG (1, 2, 4, 8, <DISABLED>))"));
	Serial.println(F("<< CMDHelp: MEMFREE"));
}





ColorduinoController::ColorduinoController()
{
	Buzzer = new BuzzerController();
	HaveToExitEvent = false;
	WaitForConsole = false;
	WaitForSending = false;
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
	WaitForConsole = profile.WaitForConsole;
	WaitForSending = profile.WaitForSending;

	cmdCallback.addCmd(PSTR("PLAYMODE"), &ColorduinoController_CMDPlayMode);
	cmdCallback.addCmd(PSTR("SAVE"), &ColorduinoController_CMDSave);
	cmdCallback.addCmd(PSTR("BEEP"), &ColorduinoController_CMDBeep);
	cmdCallback.addCmd(PSTR("STATICTEXT"), &ColorduinoController_CMDStaticText);
	cmdCallback.addCmd(PSTR("STATICTEXT3X5"), &ColorduinoController_CMDStaticText3x5);
	cmdCallback.addCmd(PSTR("TEXT"), &ColorduinoController_CMDText);
	cmdCallback.addCmd(PSTR("ICON"), &ColorduinoController_CMDIcon);
	cmdCallback.addCmd(PSTR("PIXEL"), &ColorduinoController_CMDPixel);
	cmdCallback.addCmd(PSTR("CLEAR"), &ColorduinoController_CMDClear);
	cmdCallback.addCmd(PSTR("SEND"), &ColorduinoController_CMDSend);
	cmdCallback.addCmd(PSTR("SETTING"), &ColorduinoController_CMDSetting);
	cmdCallback.addCmd(PSTR("MEMFREE"), &ColorduinoController_CMDMemFree);
	cmdCallback.addCmd(PSTR("HELP"), &ColorduinoController_CMDHelp);
	
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
			FullCheckRoutine();
			SendToAllClient();
		}
		break;
	}
	
	CleanUpPixel(0);
	CleanUpPixel(1);
	CleanUpPixel(2);
	CleanUpPixel(3);

	SendToAllClient();
}

void ColorduinoController::SetLanguageString(byte index)
{
	strcpy_P(languageString, (char*)pgm_read_word(&string_table[index]));
}

void ColorduinoController::CheckRoutine()
{
	wdt_reset();

	if (!WaitForConsole)
		cmdCallback.updateCmdProcessing(&cmdParser, &cmdBuffer, &Serial);

	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void ColorduinoController::FullCheckRoutine()
{
	wdt_reset();
	HaveToExitEvent = false;

	if (WaitForConsole)
	{
		if (cmdBuffer.readFromSerial(&Serial))
		{
			if (cmdParser.parseCmd(&cmdBuffer) != CMDPARSER_ERROR)
			{
				cmdCallback.processCmd(&cmdParser);
				cmdBuffer.clear();
			}
		}
	}
}

void ColorduinoController::SetConsoleEcho(bool echo)
{
	cmdBuffer.setEcho(echo);
}