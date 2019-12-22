#include "ColorduinoController.h"

void ColorduinoController::SetPixel(byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue)
{
	if (x < 8 && y < 8)
	{
		byte Pixel = (y * 8) + x;   //Convert from x,y to pixel number in array
		DisplayByte[AddressColor][0][Pixel] = Red;
		DisplayByte[AddressColor][1][Pixel] = Green;
		DisplayByte[AddressColor][2][Pixel] = Blue;
	}
}

void ColorduinoController::SetPixelArea(byte AddressColor, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue)
{
	if (x < 8 && y < 8)
	{
		byte _x, _y;
		for (_y = y; _y < (y + h); _y++)
		{
			for (_x = x; _x < (x + w); _x++)
			{
				SetPixel(AddressColor, _x, _y, Red, Green, Blue);
			}
		}
	}
}

void ColorduinoController::SetPixelTopLeft(byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue)
{
	SetPixel(AddressColor, 7 - y, x, Red, Green, Blue);
}

void ColorduinoController::SetPixelAreaTopLeft(byte AddressColor, byte x, byte y, byte w, byte h, byte Red, byte Green, byte Blue)
{
	if (x < 8 && y < 8)
	{
		byte _x, _y;
		for (_y = y; _y < (y + h); _y++)
		{
			for (_x = x; _x < (x + w); _x++)
			{
				SetPixelTopLeft(AddressColor, _x, _y, Red, Green, Blue);
			}
		}
	}
}

void ColorduinoController::FillPixel(byte AddressColor, byte Red, byte Green, byte Blue)
{
	unsigned char x, y;
	for (y = 0; y < SCREENSIZEY; y++)
	{
		for (x = 0; x < SCREENSIZEX; x++)
		{
			byte Pixel = (y * 8) + x;   //Convert from x,y to pixel number in array
			DisplayByte[AddressColor][0][Pixel] = Red;
			DisplayByte[AddressColor][1][Pixel] = Green;
			DisplayByte[AddressColor][2][Pixel] = Blue;
		}
	}
}

void ColorduinoController::CleanUpPixel(byte AddressColor)
{
	for (char y = 0; y < SCREENSIZEY; y++)
	{
		for (char x = 0; x < SCREENSIZEX; x++)
		{
			byte Pixel = (y * 8) + x;   //Convert from x,y to pixel number in array
			DisplayByte[AddressColor][0][Pixel] = 0;
			DisplayByte[AddressColor][1][Pixel] = 0;
			DisplayByte[AddressColor][2][Pixel] = 0;
		}
	}
}

void ColorduinoController::DrawNumber3x5(byte number, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue)
{
	if (x < 8 && y < 8)
	{
		switch (number)
		{
		case 1:
			// . 1 .
			// . 1 .
			// . 1 .
			// . 1 .
			// . 1 .
			SetPixelAreaTopLeft(AddressColor, x + 1, y, 1, 5, Red, Green, Blue);//1
			break;
		case 2:
			// 1 1 1
			// . . 2
			// 3 3 3
			// 4 . .
			// 5 5 5
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 2, y + 1, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x, y + 2, 3, 1, Red, Green, Blue);//3
			SetPixelTopLeft(AddressColor, x, y + 3, Red, Green, Blue);//4
			SetPixelAreaTopLeft(AddressColor, x, y + 4, 3, 1, Red, Green, Blue);//5
			break;
		case 3:
			// 1 1 4
			// . . 4
			// 2 2 4
			// . . 4
			// 3 3 4
			SetPixelAreaTopLeft(AddressColor, x, y, 2, 1, Red, Green, Blue);//1
			SetPixelAreaTopLeft(AddressColor, x, y + 2, 2, 1, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x, y + 4, 2, 1, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//4
			break;
		case 4:
			// 1 . 3
			// 1 . 3
			// 1 2 3
			// . . 3
			// . . 3
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 3, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//3
			break;
		case 5:
			// 1 1 1
			// 2 . .
			// 3 3 3
			// . . 4
			// 5 5 5
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x, y + 1, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x, y + 2, 3, 1, Red, Green, Blue);//3
			SetPixelTopLeft(AddressColor, x + 2, y + 3, Red, Green, Blue);//4
			SetPixelAreaTopLeft(AddressColor, x, y + 4, 3, 1, Red, Green, Blue);//5
			break;
		case 6:
			// 1 1 1
			// 2 . .
			// 2 5 4
			// 2 . 4
			// 2 3 4
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelAreaTopLeft(AddressColor, x, y + 1, 1, 4, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 1, y + 4, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x + 2, y + 2, 1, 3, Red, Green, Blue);//4
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//5
			break;
		case 7:
			// 1 1 2
			// . . 2
			// . . 2
			// . . 2
			// . . 2
			SetPixelAreaTopLeft(AddressColor, x, y, 2, 1, Red, Green, Blue);//1
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//2
			break;
		case 8:
			// 1 2 5
			// 1 . 5
			// 1 3 5
			// 1 . 5
			// 1 4 5
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 5, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//3
			SetPixelTopLeft(AddressColor, x + 1, y + 4, Red, Green, Blue);//4
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//5
			break;
		case 9:
			// 1 2 4
			// 1 . 4
			// 1 3 4
			// . . 4
			// . . 4
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 3, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//4
			break;
		default:
			// 1 2 4
			// 1 . 4
			// 1 . 4
			// 1 . 4
			// 1 3 4
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 5, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 1, y + 4, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//4
			break;
		}
	}
}

void ColorduinoController::DrawNumber3x5Char(char number, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue)
{
	switch (number)
	{
	case '1':
		DrawNumber3x5(1, AddressColor, x, y, Red, Green, Blue);
		break;
	case '2':
		DrawNumber3x5(2, AddressColor, x, y, Red, Green, Blue);
		break;
	case '3':
		DrawNumber3x5(3, AddressColor, x, y, Red, Green, Blue);
		break;
	case '4':
		DrawNumber3x5(4, AddressColor, x, y, Red, Green, Blue);
		break;
	case '5':
		DrawNumber3x5(5, AddressColor, x, y, Red, Green, Blue);
		break;
	case '6':
		DrawNumber3x5(6, AddressColor, x, y, Red, Green, Blue);
		break;
	case '7':
		DrawNumber3x5(7, AddressColor, x, y, Red, Green, Blue);
		break;
	case '8':
		DrawNumber3x5(8, AddressColor, x, y, Red, Green, Blue);
		break;
	case '9':
		DrawNumber3x5(9, AddressColor, x, y, Red, Green, Blue);
		break;
	default:
		DrawNumber3x5(0, AddressColor, x, y, Red, Green, Blue);
		break;
	}
}

void ColorduinoController::DrawUnit3x5(char unit, byte AddressColor, byte x, byte y, byte Red, byte Green, byte Blue)
{
	if (x < 8 && y < 8)
	{
		switch (unit)
		{
		case 'd':
			// 1 1 1
			// 3 . 2
			// 4 4 4
			// . . .
			// . . .
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 2, y + 1, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x, y + 1, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x, y + 2, 3, 1, Red, Green, Blue);//4
			break;
		case 'b':
			// 1 2 .
			// 1 . 3
			// 1 4 .
			// 1 . 5
			// 1 6 .
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 5, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 2, y + 1, Red, Green, Blue);//3
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//4
			SetPixelTopLeft(AddressColor, x + 2, y + 3, Red, Green, Blue);//5
			SetPixelTopLeft(AddressColor, x + 1, y + 4, Red, Green, Blue);//6
			break;
		case 'm':
			// 1 . 3
			// 1 2 3
			// 1 . 3
			// 1 . 3
			// 1 . 3
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 5, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y + 1, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 5, Red, Green, Blue);//3
			break;
		case 'k':
			// 1 . 3
			// 1 . 3
			// 1 2 .
			// 1 . 4
			// 1 . 4
			SetPixelAreaTopLeft(AddressColor, x, y, 1, 5, Red, Green, Blue);//1
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x + 2, y, 1, 2, Red, Green, Blue);//3
			SetPixelAreaTopLeft(AddressColor, x + 2, y + 3, 1, 2, Red, Green, Blue);//4
			break;
		case 'c':
			// 1 1 1
			// 2 . .
			// 2 . .
			// 2 . .
			// 3 3 3
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelAreaTopLeft(AddressColor, x, y + 1, 1, 3, Red, Green, Blue);//2
			SetPixelAreaTopLeft(AddressColor, x, y + 4, 3, 1, Red, Green, Blue);//3
			break;
		case 'f':
			// 1 1 1
			// 2 . .
			// 2 3 .
			// 2 . .
			// 2 . .
			SetPixelAreaTopLeft(AddressColor, x, y, 3, 1, Red, Green, Blue);//1
			SetPixelAreaTopLeft(AddressColor, x, y + 1, 1, 4, Red, Green, Blue);//2
			SetPixelTopLeft(AddressColor, x + 1, y + 2, Red, Green, Blue);//3
			break;
		case '.':
			// . . .
			// . . .
			// . . .
			// . . .
			// . 1 .
			SetPixelTopLeft(AddressColor, x + 1, y + 4, Red, Green, Blue);//1
			break;
		}
	}
}

void ColorduinoController::DrawChar(byte AddressColor, int16_t x, int16_t y, unsigned char c, byte Red, byte Green, byte Blue)
{
	if ((x >= SCREENSIZEX) || // Clip right
		(y >= SCREENSIZEY) || // Clip bottom
		((x + 5) < 0) || // Clip left
		((y + 7) < 0))   // Clip top
		return;

	for (int8_t i = 0; i < 6; i++)
	{
		uint8_t line;
		if (i == 5)
			line = 0x0;
		else
			line = pgm_read_byte(CharPixel + (c * 5) + i);

		for (int8_t j = 0; j < 8; j++)
		{
			if (line & 0x1)
			{
				//drawPixel(x+i, y+j, color);
				SetPixel(AddressColor, -y - j + 6, x + i, Red, Green, Blue);
			}
			line >>= 1;
		}
	}
}

void ColorduinoController::DrawImage8x8(byte AddressColor, int16_t x, int16_t y, const unsigned char c[])
{
	if ((x >= SCREENSIZEX) || // Clip right
		(y >= SCREENSIZEY) || // Clip bottom
		((x + 5) < 0) || // Clip left
		((y + 7) < 0))   // Clip top
		return;

	for (int8_t i = 0; i < 8; i++)
	{
		for (int8_t j = 0; j < 8; j++)
		{
			uint8_t part1 = pgm_read_byte(c + (j * 16) + (i * 2));
			uint8_t part2 = pgm_read_byte(c + (j * 16) + (i * 2 + 1));

			uint16_t rgb565 = part2 | part1 << 8;

			uint8_t r = (rgb565 & 0xF800) >> 11;
			uint8_t g = (rgb565 & 0x07E0) >> 5;
			uint8_t b = rgb565 & 0x001F;

			r = (r * 255) / 31;
			g = (g * 255) / 63;
			b = (b * 255) / 31;

			SetPixel(AddressColor, -y - j + 7, x + i, r, g, b);
		}
	}
}