#include <stdio.h>
#pragma warning( disable : 6031)

int sign(const double x)
{
	if (x < 0)
		return -1;
	if (x == 0)
		return 0;
	return 1;
}

int main(void)
{
	double a = 0.0, b = 0.0;
	printf("A = ");
	scanf("%lf", &a);
	printf("B = ");
	scanf("%lf", &b);
	printf("Sign(A)+Sign(B) = %d", sign(a) + sign(b));
}
