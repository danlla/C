#include <stdio.h>
#pragma warning( disable : 6031)

const double PI = 3.14;

double area(double r);

double circumference(double r);

int main(void)
{
	printf("Enter radius\nR = ");
	double r = 0.0;
	scanf("%lf", &r);
	while (r <= 0.0)
	{
		printf("Invalid value\nR = ");
		scanf("%lf", &r);
	}
	printf("Circumference L = %lf\nArea of a circle S = %lf\n", circumference(r), area(r));
	return 0;
}

double area(const double r)
{
	return PI * r*r;
}

double circumference(const double r)
{
	return 2 * PI*r;
}
