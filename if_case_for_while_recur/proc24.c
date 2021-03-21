#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool even(const int k)
{
	
	if (k % 2 == 0)
		return true;
	return false;
}

int main(void)
{
	int x = 0, amount = 0;
	for (int i = 0; i < 10; i++)
	{
		printf("X = ");
		scanf("%d", &x);
		if (even(x))
			++amount;
	}
	printf("Amount even number = %d", amount);
}