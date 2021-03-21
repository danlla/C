#include <stdio.h>
#include <stdbool.h>
#pragma warning( disable : 6031)

bool is_prime(const int n)
{
	for (int i = 2; i <= n / 2; ++i)
		if (n % i == 0)
			return false;
	return true;
}

int enter_number(int i)
{
	int num = 0;
	printf("enter %d number: ", i + 1);
	scanf("%d", &num);
	while (num <= 1)
	{
		printf("enter number: ");
		scanf("%d", &num);
	}
	return num;
}


int main(void)
{
	int num = 0;
	int count_prime = 0;
	for (int i = 0; i < 10; ++i)
	{
		num = enter_number(i);
		if (is_prime(num))
			++count_prime;
	}
	printf("count prime number: %d", count_prime);
}