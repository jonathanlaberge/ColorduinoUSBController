#ifndef	hNumberFormat
#define hNumberFormat

#include "Arduino.h"

String NumberFormat(unsigned long long n, int iteration);
unsigned long long CharToULongLong(char *str);
char* SplitChar(char* inputString, char *separator, int segmentNumber);

#endif