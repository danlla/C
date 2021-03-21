#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	printf("Enter number: ");
	int num = 0;
	scanf("%d", &num);
	while (num < 1 || num>999)
	{
		printf("Enter number: ");
		scanf("%d", &num);
	}
	if (num % 2 == 0)
		printf("Even ");
	else
		printf("Odd ");
	if (num / 100 >= 1)
		printf("three-digit ");
	else if (num / 10 >= 1)
			printf("two-digit ");
		 else
			printf("one-digit ");
	printf("number");
}
