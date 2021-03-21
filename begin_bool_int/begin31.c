#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	printf("T(F) = ");
	double t = 0.0;
	scanf("%lf", &t);
	printf("T(C) = %lf", (t-32)*(5.0/9.0));
	return 0;
}