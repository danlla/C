#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int n = 0;
	printf("N = ");
	scanf("%d", &n);
	double x = 0.0, sum = 0.0, mul = 1.0;
	for (int i = 0; i < n; i++)
	{
		printf("X = ");
		scanf("%lf", &x);
		sum += x;
		mul *= x;
	}
	printf("Sum = %lf\nMul = %lf", sum, mul);
}
