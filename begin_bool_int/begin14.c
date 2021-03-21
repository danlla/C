#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	const double pi = 3.14;
	printf("Circumference\nL = ");
	double l = 0.0;
	scanf("%lf", &l);
	while (l <= 0.0)
	{
		printf("Invalid value\nL = ");
		scanf("%lf", &l);
	}
	double r = l / (2 * pi);
	printf("Radius = %lf\nArea of a circle = %lf\n", r, pi*r*r);
	return 0;
}