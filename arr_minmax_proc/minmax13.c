#include <stdio.h>
#include <stdlib.h>
#pragma warning( disable : 6031)

int odd_max_index(const int* const numbers, const size_t n)
{
	int odd_max = numbers[0];
	int odd_max_index = -1;
	for (size_t i = 0; i < n; ++i)
	{
		if (numbers[i] > odd_max && numbers[i] % 2)
		{
			odd_max = numbers[i];
			odd_max_index = i;
		}
	}
	return odd_max_index;
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

	int odd_max_i = odd_max_index(numbers, n);
	printf("odd max number index = %d", odd_max_i);
	free(numbers);
}