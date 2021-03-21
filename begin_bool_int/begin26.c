#include <stdio.h>
#include <math.h>
#pragma warning( disable : 6031)

int main()
{
	printf("x = ");
	double x = 0.0;
	scanf("%lf", &x);
	printf("f(x) = %lf", 4 * pow(x - 3, 6) - 7 * pow(x - 3, 3) + 2);
	return 0;
}