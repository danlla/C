#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool between(int a, int b, int c)
{
	return a < b&& b < c;
}

int main()
{
	int a, b, c;
	a = b = c = 0;
	printf("A = ");
	scanf("%d", &a);
	printf("B = ");
	scanf("%d", &b);
	printf("C = ");
	scanf("%d", &c);
	bool check = between(a, b, c);
	printf("%d", check);
	return 0;
}