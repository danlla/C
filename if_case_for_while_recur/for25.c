#include <stdio.h>
#include <math.h>
#pragma warning( disable : 6031)

int main(void)
{
	double x = 0.0;
	printf("x = ");
	scanf("%lf", &x);
	while (fabs(x)>1)
	{
		printf("-1<x<1\nx = ");
		scanf("%lf", &x);
	}
	int n = 0;
	printf("N = ");
	scanf("%d", &n);
	while (n < 1)
	{
		printf("N>0\nN = ");
		scanf("%d", &n);
	}
	double res = 0.0;
	for (int i = 0; i < n; i++)
		res += pow(-1, i)*pow(x, i + 1)*((double)1 / (i+1));
	printf("ln(%lf) = %lf", x+1.0, res);
}