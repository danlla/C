#include <stdio.h>
#pragma warning( disable : 6031)

int sum_range(int a, int b)
{
	int sum = 0;
	for (; a <= b; ++a)
		sum += a;
	return sum;
}

int main(void)
{
	int a = 0, b = 0, c = 0;
	printf("enter A = ");
	scanf("%d", &a);
	printf("enter B = ");
	scanf("%d", &b);
	printf("enter C = ");
	scanf("%d", &c);
	printf("sum from A to B = %d\n", sum_range(a, b));
	printf("sum from B to C = %d", sum_range(b, c));
}
