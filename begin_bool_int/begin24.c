#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	double a, b, c;
	a = b = c = 0.0;
	printf("A = ");
	scanf("%lf", &a);
	printf("B = ");
	scanf("%lf", &b);
	printf("C = ");
	scanf("%lf", &c);
	double tmp = c;
	c = a;
	a = b;
	b = tmp;
	printf("A = %lf\nB = %lf\nC = %lf", a, b, c);
	return 0;
}