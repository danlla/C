#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool monotonic(const unsigned num)
{
	const unsigned first_digit = num / 100;
	const unsigned second_digit = (num % 100) / 10;
	const unsigned third_digit = (num % 100) % 10;

	return (third_digit < second_digit && second_digit < first_digit) || (first_digit < second_digit && second_digit < third_digit);
}

int main(void)
{
	unsigned num = 0;
	printf("Number = ");
	scanf("%u", &num);
	while ((num / 100) > 9 || (num / 100) == 0)
	{
		printf("Invalid value\nNumber = ");
		scanf("%u", &num);
	}
	bool check = monotonic(num);
	printf("%d", check);
	return 0;
}