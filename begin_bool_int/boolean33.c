#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool triangle_exists(unsigned a, unsigned b, unsigned c)
{
	return (a + b > c) && (a + c > b) && (b + c > a) && (a - b < c) && (a - c < b) && (b - c < a);
}

int main()
{
	unsigned a, b, c;
	a = b = c = 0;
	printf("a = ");
	scanf("%u", &a);
	printf("b = ");
	scanf("%u", &b);
	printf("c = ");
	scanf("%u", &c);
	bool check = triangle_exists(a, b, c);
	printf("%d", check);
	return 0;
}