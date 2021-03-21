#include <stdio.h>
#pragma warning( disable : 6031)

int fib1(int n, int *call_amount)
{
	if (n == 1 || n == 2)
		return 1;
	else
		++(*call_amount);
		return fib1(n-1, call_amount)+fib1(n-2, call_amount) ;
}

int main(void)
{
	for (int i = 0; i < 5; i++)
	{
		int n = 0;
		int call_amount = 0;
		printf("\nN = ");
		scanf("%d", &n);
		printf("fib(%d) = %d", n, fib1(n, &call_amount));
		printf("\ncall amount = %d", call_amount);
	}
}