#include "ColorduinoController.h"


void ColorduinoController::ScrollText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue)
{
	for (Time < 0; Time--;)
	{
		if (HaveToExitEvent == true) break;
		for (int XMove = 24; XMove < ((strlen(Text) * 6 + 8)); XMove++)
		{
			if (HaveToExitEvent == true) break;
			FillPixel(0, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(1, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(2, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(3, BackgroundRed, BackgroundGreen, BackgroundBlue);
			for (int Char = 0; Char < strlen(Text); Char++)
			{
				DrawChar(3, -XMove + (Char * 6) + 10, 0, Text[Char], Red, Green, Blue);
				DrawChar(2, -XMove + (Char * 6) + 18, 0, Text[Char], Red, Green, Blue);
				DrawChar(1, -XMove + (Char * 6) + 26, 0, Text[Char], Red, Green, Blue);
				DrawChar(0, -XMove + (Char * 6) + 34, 0, Text[Char], Red, Green, Blue);
			}
			SendToClient(DestI2CAddress1, 0);
			SendToClient(DestI2CAddress2, 1);
			SendToClient(DestI2CAddress3, 2);
			SendToClient(DestI2CAddress4, 3);
			delay(Speed);
		}
	}
}

void ColorduinoController::StaticText(uint16_t Time, uint16_t Speed, char* Text, byte Red, byte Green, byte Blue, byte BackgroundRed, byte BackgroundGreen, byte BackgroundBlue)
{
	for (Time < 0; Time--;)
	{
		if (HaveToExitEvent == true) break;

		if (BackgroundRed || BackgroundGreen || BackgroundBlue)
		{
			FillPixel(0, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(1, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(2, BackgroundRed, BackgroundGreen, BackgroundBlue);
			FillPixel(3, BackgroundRed, BackgroundGreen, BackgroundBlue);
		}

		for (int i = 0; i < strlen(Text); i++)
		{
			if (HaveToExitEvent == true) break;
			DrawChar(0, i * 6, 0, Text[i], Red, Green, Blue);
			DrawChar(1, i * 6 - 8, 0, Text[i], Red, Green, Blue);
			DrawChar(2, i * 6 - 16, 0, Text[i], Red, Green, Blue);
			DrawChar(3, i * 6 - 24, 0, Text[i], Red, Green, Blue);
		}
		if (Speed != 0)
		{
			SendToClient(DestI2CAddress1, 0);
			SendToClient(DestI2CAddress2, 1);
			SendToClient(DestI2CAddress3, 2);
			SendToClient(DestI2CAddress4, 3);
			delay(Speed);
		}
	}
}

void ColorduinoController::StaticText3x5(char* Text, byte StartingScreen, byte x, byte y, byte Red, byte Green, byte Blue)
{
	if (!(x != 0 && x != 4))
		x = 0;
	for (int i = 0; i < strlen(Text); i++)
	{
		if (HaveToExitEvent == true) break;

		if (isDigit(Text[i]))
		{
			DrawNumber3x5Char(Text[i], StartingScreen, x, y, Red, Green, Blue);
			if (x == 4)
				StartingScreen++;

			if (x == 0)
				x = 4;
			else
				x = 0;
		}
		else if (Text[i] == '.' || Text[i] == 'k' || Text[i] == 'm' || Text[i] == 'b' || Text[i] == 'd' || Text[i] == 'f' || Text[i] == 'c')
		{
			DrawUnit3x5(Text[i], StartingScreen, x, y, Red, Green, Blue);
			if (x == 4)
				StartingScreen++;

			if (x == 0)
				x = 4;
			else
				x = 0;
		}
	}
	SendToClient(DestI2CAddress1, 0);
	SendToClient(DestI2CAddress2, 1);
	SendToClient(DestI2CAddress3, 2);
	SendToClient(DestI2CAddress4, 3);
}

void ColorduinoController::PlasmaSolo(uint16_t Time, uint16_t Speed)
{
	unsigned char plasma[SCREENSIZEX][SCREENSIZEY];
	long paletteShift;
	paletteShift = 128000;
	unsigned char bcolor;
	//generate the plasma once
	for (unsigned char y = 0; y < SCREENSIZEY; y++)
	{
		for (unsigned char x = 0; x < SCREENSIZEX; x++)
		{
			//the plasma buffer is a sum of sines
			bcolor = (unsigned char)(128.0 + (128.0 * sin(x * 8.0 / 16.0)) + 128.0 + (128.0 * sin(y * 8.0 / 16.0))) / 2;
			plasma[x][y] = bcolor;
		}
	}
	for (Time < 0; Time--;)
	{
		unsigned char x, y;
		float value;
		ColorRGB colorRGB;
		ColorHSV colorHSV;
		for (y = 0; y < SCREENSIZEY; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = sin(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + sin(Dist(x, y, 64.0, 64.0) / 8.0) + sin(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + sin(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(0, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
				SetPixel(1, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
				SetPixel(2, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
				SetPixel(3, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		paletteShift++;
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
		delay(Speed);
	}
}

void ColorduinoController::PlasmaAll(uint16_t Time, uint16_t Speed)
{
	unsigned char plasma[SCREENSIZEX][SCREENSIZEY];
	long paletteShift;
	paletteShift = 128000;
	unsigned char bcolor;

	for (Time < 0; Time--;)
	{
		unsigned char x, y;
		float value;
		ColorRGB colorRGB;
		ColorHSV colorHSV;
		for (y = 0; y < SCREENSIZEY; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = sin(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + sin(Dist(x, y, 64.0, 64.0) / 8.0) + sin(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + sin(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(0, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 8; y < SCREENSIZEY + 8; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = sin(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + sin(Dist(x, y, 64.0, 64.0) / 8.0) + sin(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + sin(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(1, x, y - 8, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 16; y < SCREENSIZEY + 16; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = sin(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + sin(Dist(x, y, 64.0, 64.0) / 8.0) + sin(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + sin(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(2, x, y - 16, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 24; y < SCREENSIZEY + 24; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = sin(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + sin(Dist(x, y, 64.0, 64.0) / 8.0) + sin(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + sin(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(3, x, y - 24, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		paletteShift++;
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
		delay(Speed);
	}
}

void ColorduinoController::PlasmaAllCos(uint16_t Time, uint16_t Speed)
{
	unsigned char plasma[SCREENSIZEX][SCREENSIZEY];
	long paletteShift;
	paletteShift = 128000;
	unsigned char bcolor;

	for (Time < 0; Time--;)
	{
		unsigned char x, y;
		float value;
		ColorRGB colorRGB;
		ColorHSV colorHSV;
		for (y = 0; y < SCREENSIZEY; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = cos(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + cos(Dist(x, y, 64.0, 64.0) / 8.0) + cos(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + cos(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(0, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 8; y < SCREENSIZEY + 8; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = cos(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + cos(Dist(x, y, 64.0, 64.0) / 8.0) + cos(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + cos(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(1, x, y - 8, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 16; y < SCREENSIZEY + 16; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = cos(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + cos(Dist(x, y, 64.0, 64.0) / 8.0) + cos(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + cos(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(2, x, y - 16, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 24; y < SCREENSIZEY + 24; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = cos(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + cos(Dist(x, y, 64.0, 64.0) / 8.0) + cos(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + cos(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(3, x, y - 24, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		paletteShift++;
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
		delay(Speed);
	}
}

void ColorduinoController::PlasmaAllTan(uint16_t Time, uint16_t Speed)
{
	unsigned char plasma[SCREENSIZEX][SCREENSIZEY];
	long paletteShift;
	paletteShift = 128000;
	unsigned char bcolor;

	for (Time < 0; Time--;)
	{
		unsigned char x, y;
		float value;
		ColorRGB colorRGB;
		ColorHSV colorHSV;
		for (y = 0; y < SCREENSIZEY; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = tan(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + tan(Dist(x, y, 64.0, 64.0) / 8.0) + tan(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + tan(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(0, x, y, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 8; y < SCREENSIZEY + 8; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = tan(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + tan(Dist(x, y, 64.0, 64.0) / 8.0) + tan(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + tan(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(1, x, y - 8, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 16; y < SCREENSIZEY + 16; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = tan(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + tan(Dist(x, y, 64.0, 64.0) / 8.0) + tan(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + tan(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(2, x, y - 16, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		for (y = 24; y < SCREENSIZEY + 24; y++)
		{
			for (x = 0; x < SCREENSIZEX; x++)
			{
				value = tan(Dist(x + paletteShift, y, 128.0, 128.0) / 8.0) + tan(Dist(x, y, 64.0, 64.0) / 8.0) + tan(Dist(x, y + paletteShift / 7, 192.0, 64) / 7.0) + tan(Dist(x, y, 192.0, 100.0) / 8.0);
				colorHSV.h = (unsigned char)((value) * 128) & 0xff;
				colorHSV.s = 255;
				colorHSV.v = 255;
				HSVtoRGB(&colorRGB, &colorHSV);
				SetPixel(3, x, y - 24, colorRGB.r, colorRGB.g, colorRGB.b);
			}
		}
		paletteShift++;
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
		delay(Speed);
	}
}

void ColorduinoController::ColorFader(uint16_t Time)
{
	uint8_t Red = 0, Green = 0, Blue = 255;
	int8_t rd = 5, gd = 0, bd = 0;
	for (Time < 0; Time--;)
	{
		Red += rd;
		Green += gd;
		Blue += bd;

		if (bd < 0 && Blue == 0) { bd = 0; gd = 5; }
		if (gd > 0 && Green == 255) { gd = 0; rd = -5; }
		if (rd < 0 && Red == 0) { rd = 0; bd = 5; }
		if (bd > 0 && Blue == 255) { bd = 0; gd = -5; }
		if (gd < 5 && Green == 0) { gd = 0; rd = 5; }
		if (rd > 0 && Red == 255) { bd = -5; rd = 0; }
		FillPixel(0, Red, Green, Blue);
		FillPixel(1, Red, Green, Blue);
		FillPixel(2, Red, Green, Blue);
		FillPixel(3, Red, Green, Blue);
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
	}
}

void ColorduinoController::FullColor(uint16_t Time, byte Red, byte Green, byte Blue)
{
	for (Time < 0; Time--;)
	{
		FillPixel(0, Red, Green, Blue);
		FillPixel(1, Red, Green, Blue);
		FillPixel(2, Red, Green, Blue);
		FillPixel(3, Red, Green, Blue);
		SendToClient(DestI2CAddress1, 0);
		SendToClient(DestI2CAddress2, 1);
		SendToClient(DestI2CAddress3, 2);
		SendToClient(DestI2CAddress4, 3);
		if (HaveToExitEvent == true) break;
	}
}

void ColorduinoController::Loading(byte Screen, uint16_t Time)
{
	byte ScreenDest;
	for (Time < 0; Time--;)
	{
		if (Screen == 1) ScreenDest = DestI2CAddress1;
		else if (Screen == 2) ScreenDest = DestI2CAddress2;
		else if (Screen == 3) ScreenDest = DestI2CAddress3;
		else ScreenDest = DestI2CAddress4;
		SendToClient(ScreenDest, Screen);
		CleanUpPixel(Screen);
		DrawChar(Screen, 1, 1, '/', 255, 255, 255);
		delay(20);
		SendToClient(ScreenDest, Screen);
		CleanUpPixel(Screen);
		DrawChar(Screen, 1, 1, '-', 255, 255, 255);
		delay(20);
		SendToClient(ScreenDest, Screen);
		CleanUpPixel(Screen);
		DrawChar(Screen, 1, 1, '\\', 255, 255, 255);
		delay(20);
		SendToClient(ScreenDest, Screen);
		CleanUpPixel(Screen);
		DrawChar(Screen, 1, 1, '|', 255, 255, 255);
		delay(20);
		if (HaveToExitEvent == true) break;
	}
	CleanUpPixel(0);
	CleanUpPixel(1);
	CleanUpPixel(2);
	CleanUpPixel(3);
	SendToClient(ScreenDest, Screen);
}