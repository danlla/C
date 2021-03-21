#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	unsigned num = 0;
	printf("Number = ");
	scanf("%u", &num);
	while ((num / 100) >9 || (num/100)==0)
	{
		printf("Invalid value\nNumber = ");
		scanf("%u", &num);
	}
	unsigned right = num % 10;
	num = num / 10;
	num += right * 100;
	printf("Number = %u", num);
	return 0;
}