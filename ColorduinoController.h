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
	void DrawChar(byte AddressColor, int16_t x, int16_t y, unsigned char c, byte Red, byte Green, byte Blue);
	void DrawImage8x8(byte AddressColor, int16_t x, int16_t y, const unsigned char c[]);
	void CleanUpPixel(byte AddressColor);
	void DrawNumber3x5(byte number, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue);
	void DrawNumber3x5Char(char number, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue);
	void DrawUnit3x5(char unit, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue);
	void FillPixel(byte AddressColor, byte Red, byte Green, byte Blue);
	void SetPixel(byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue);
	void SetPixelArea(byte AddressColor, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue);
	void SetPixelTopLeft(byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue);
	void SetPixelAreaTopLeft(byte AddressColor, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue);
	void HSVtoRGB(void *vRGB, void *vHSV);
	void Loading(byte Screen, uint16_t Time);
	void ColorFader(uint16_t Time);
	void FullColor(uint16_t Time, byte Red, byte Green, byte Blue);
	void PlasmaAll(uint16_t Time, uint16_t Speed);
	void PlasmaSolo(uint16_t Time, uint16_t Speed);
	void StaticText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue);
	void StaticText3x5(char * Text, byte startingScreen, byte x, byte y, byte Red, byte Green, byte Blue);
	void ScrollText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue);
	bool HaveToExitEvent;
	byte PlayMode;
	BuzzerController *Buzzer;
private:
	ColorduinoController();
	void SendToClient(byte AddressI2C, byte AddressColor);
	void CheckRoutine();
	void FullCheckRoutine();
	void SendToClientI2CControl(byte AddressI2C, byte Color, byte* Data);
	float Dist(float a, float b, float c, float d);
	unsigned int RGBtoINT(void *vRGB);
	static ColorduinoController* instance;
	byte DisplayByte[4][3][64]; //Display array - 64 bytes x 3 colours
	char languageString[64];
	CmdCallback_P<5> cmdCallback;
	CmdBuffer<32> cmdBuffer;
	CmdParser cmdParser;
};

#endif
