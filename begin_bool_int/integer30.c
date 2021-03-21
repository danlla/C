#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	unsigned year = 0;
	printf("Year = ");
	scanf("%u", &year);
	while (year <= 0)
	{
		printf("Invalid value\nYear = ");
		scanf("%u", &year);
	}
	unsigned century = year / 100;
	if (year % 100 > 0)
		++century;
	printf("Century: %u", century);
	return 0;
} 