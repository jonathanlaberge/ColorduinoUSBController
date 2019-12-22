#ifndef hConfiguration
#define hConfiguration

#define Enable_WireTransmission

#define Config_Pin_Beeper 2

#define Config_Serial_Speed 115200
#define Config_WatchDog_Timeout WDTO_8S

#define DestI2CAddress1 0x05
#define DestI2CAddress2 0x06
#define DestI2CAddress3 0x07
#define DestI2CAddress4 0x08

#define START_OF_DATA 0x10
#define END_OF_DATA 0x20

#define SCREENSIZEX 8
#define SCREENSIZEY 8

#define CMD_BUFFER_SIZE 128

#endif
