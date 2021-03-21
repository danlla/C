#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	printf("Enter x: ");
	double x = 0.0;
	scanf("%lf", &x);
	double res = 0.0;
	if (x <= 0)
		res = -x;
	if (x > 0 && x < 2)
		res = x * x;
	if (x >= 2)
		res = 4;
	printf("f = %lf", res);
}