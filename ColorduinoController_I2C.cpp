#include "ColorduinoController.h"


void ColorduinoController::SendToClient(byte AddressI2C, byte AddressColor)
{
	SendToClientI2CControl(AddressI2C, 0, DisplayByte[AddressColor][0]);
	SendToClientI2CControl(AddressI2C, 1, DisplayByte[AddressColor][1]);
	SendToClientI2CControl(AddressI2C, 2, DisplayByte[AddressColor][2]);


	CheckRoutine();
}

void ColorduinoController::SendToClientI2CControl(byte AddressI2C, byte Color, byte* Data)
{
#ifdef Enable_WireTransmission
	do
	{
		Wire.beginTransmission(AddressI2C);
		Wire.write(START_OF_DATA);
		Wire.write(Color);
		Wire.write(Data, 64);
		Wire.write(END_OF_DATA);
	} while (Wire.endTransmission() != 0);
#endif
}