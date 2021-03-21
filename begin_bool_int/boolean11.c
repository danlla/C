#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool parity(int a, int b)
{
	return (a % 2) == (b % 2);
}

int main()
{
	int a, b;
	a = b = 0;
	printf("A = ");
	scanf("%d", &a);
	printf("B = ");
	scanf("%d", &b);
	bool check = parity(a, b);
	printf("%d", check);
	return 0;
}