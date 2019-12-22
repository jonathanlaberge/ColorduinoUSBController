#include "NumberFormat.h"


/**
 * Recursive implementation, invokes itself for each factor of a thousand, increasing the class on each invokation.
 * @param n the number to format
 * @param iteration in fact this is the class from the array c
 * @return a String representing the number n formatted in a cool looking way.
 */
String NumberFormat(unsigned long long n, int iteration)
{
	if (n < 999999 && iteration == 0)
		return String((long)n);

	char c[] = { 'k', 'm', 'b', 't' };
	double d = ((double)n / 100) / 10.0;
	bool isRound = (int)(d * 10) % 10 == 0;
	if (d < 1000)
		if (d > 99.9 || isRound || (!isRound && d > 9.99))
			return String(((int)d * 10 / 10)) + c[iteration];
		else
			return String(d) + c[iteration];
	else
		return NumberFormat(d, iteration + 1);
}

unsigned long long CharToULongLong(char *str)
{
	long long result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		result = result * 10 + str[i] - '0';
	return result;
}

char* SplitChar(char* inputString, char *separator, int segmentNumber)
{
	char *act, *sub, *ptr;
	/*static */char copy[32];
	int i;

	strcpy(copy, inputString);
	for (i = 1, act = copy; i <= segmentNumber; i++, act = NULL)
	{
		sub = strtok_r(act, separator, &ptr);
		if (sub == NULL) break;
	}
	return sub;
}