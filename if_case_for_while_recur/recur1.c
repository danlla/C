#include <stdio.h>
#pragma warning( disable : 6031)

double fact(int n)
{
	if (n == 0 || n == 1)
		return 1;
	else
		return n * fact(n - 1);
}

int main(void)
{
	for (int i = 0; i < 5; i++)
	{
		int n = 0;
		printf("\nN = ");
		scanf("%d", &n);
		printf("%d! = %lf", n, fact(n));
	}
}