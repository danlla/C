#include <stdio.h>
#include <stdlib.h>
#pragma warning( disable : 6031)

void print_even_numbers_direct(const int* const numbers, const size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		if (numbers[i] % 2 == 0)
			printf("%d ", numbers[i]);
	}
}

void print_odd_numbers_invert(const int* const numbers, const size_t n)
{
	for (size_t i = 0; i <= n-1; ++i)
	{
		if (numbers[n-1-i] % 2 == 1)
			printf("%d ", numbers[n-1-i]);
	}
}

int main(void)
{
	size_t n = 0;
	printf("N = ");
	scanf("%zu", &n);
	while (n <= 0)
	{
		printf("N = ");
		scanf("%zu", &n);
	}

	int*numbers = (int*)malloc(n * sizeof(int));

	for (size_t i = 0; i < n; ++i)
	{
		printf("%zu : ", i);
		scanf("%d", numbers + i);
	}

	print_even_numbers_direct(numbers, n);
	printf("\n");
	print_odd_numbers_invert(numbers, n);
	free(numbers);
}