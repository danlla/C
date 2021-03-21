#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	unsigned num = 0;
	printf("Number = ");
	scanf("%u", &num);
	while ((num / 10) > 9 || (num / 10) == 0)
	{
		printf("Invalid value\nNumber = ");
		scanf("%u", &num);
	}
	printf("Sum = %u\nMul = %u", (unsigned)(num / 10 + num % 10), (unsigned)(num / 10 * (num % 10)));
	return 0;
}