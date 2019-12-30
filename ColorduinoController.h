#ifndef hColorduinoController
#define hColorduinoController

#include "Arduino.h"
#include "Wire64.h"
#include "PixelChar.c"
#include "BuzzerController.h"
#include "EEPROMProfile.h"
#include "EEPROMSaver.h"
#include "Language.c"
#include "PixelImage.c"
#include <avr/wdt.h>
#include "Config.h"
#include "NumberFormat.h"
#include "CmdBuffer.hpp"
#include "CmdCallback.hpp"
#include "CmdParser.hpp"
#include "Mode.c"
#include "MemoryFree.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}
ColorRGB;
typedef struct
{
	unsigned char h;
	unsigned char s;
	unsigned char v;
}
ColorHSV;

class ColorduinoController
{
public:
	static ColorduinoController* Instance();
	void Setup();
	void Loop();
	void SetLanguageString(byte index);
	void DrawChar(byte ScreenAddress, int16_t x, int16_t y, unsigned char c, byte Red, byte Green, byte Blue);
	void DrawImage8x8(byte ScreenAddress, int16_t x, int16_t y, const unsigned char c[]);
	void CleanUpPixel(byte ScreenAddress);
	void DrawNumber3x5(byte number, byte ScreenAddress, byte x, byte y, byte Red, byte Green, byte Blue);
	void DrawNumber3x5Char(char number, byte ScreenAddress, byte x, byte y, byte Red, byte Green, byte Blue);
	void DrawUnit3x5(char unit, byte ScreenAddress, byte x, byte y, byte Red, byte Green, byte Blue);
	void FillPixel(byte ScreenAddress, byte Red, byte Green, byte Blue);
	void SetPixel(byte ScreenAddress, byte x, byte y, byte Red, byte Green, byte Blue);
	void SetPixelArea(byte ScreenAddress, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue);
	void SetPixelTopLeft(byte ScreenAddress, byte x, byte y, byte Red, byte Green, byte Blue);
	void SetPixelAreaTopLeft(byte ScreenAddress, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue);
	void HSVtoRGB(void *vRGB, void *vHSV);
	void Loading(byte Screen, uint16_t Time);
	void ColorFader(uint16_t Time);
	void FullColor(uint16_t Time, byte Red, byte Green, byte Blue);
	void PlasmaAll(uint16_t Time, uint16_t Speed);
	void PlasmaAllCos(uint16_t Time, uint16_t Speed);
	void PlasmaAllTan(uint16_t Time, uint16_t Speed);
	void PlasmaSolo(uint16_t Time, uint16_t Speed);
	void StaticText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue);
	void StaticText3x5(char * Text, byte StartingScreen, byte x, byte y, byte Red, byte Green, byte Blue);
	void ScrollText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue);
	void SendToClient(byte AddressI2C, byte AddressColor);
	void SetConsoleEcho(bool echo);
	bool HaveToExitEvent;
	bool WaitForConsole;
	Mode PlayMode;
	BuzzerController *Buzzer;
private:
	ColorduinoController();
	void CheckRoutine();
	void FullCheckRoutine();
	void SendToClientI2CControl(byte AddressI2C, byte Color, byte* Data);
	float Dist(float a, float b, float c, float d);
	unsigned int RGBtoINT(void *vRGB);
	static ColorduinoController* instance;
	byte DisplayByte[4][3][64]; //Display array - 64 bytes x 3 colours
	char languageString[64];
	CmdCallback_P<12> cmdCallback;
	CmdBuffer<128> cmdBuffer;
	CmdParser cmdParser;
};

#endif
