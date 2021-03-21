#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int n = 0;
	printf("N = ");
	scanf("%d", &n);
	while (n <= 0)
	{
		printf("N = ");
		scanf("%d", &n);
	}
	while (n / 10 >= 1)
	{
		printf("%d", n % 10);
		n /= 10;
	}
	printf("%d", n);
}
