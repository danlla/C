#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool isosceles(unsigned a, unsigned b, unsigned c)
{
	return (a == b && a != c) || (a == c && a != b) || (b == c && b != a);
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
	bool check = isosceles(a, b, c);
	printf("%d", check);
	return 0;
}