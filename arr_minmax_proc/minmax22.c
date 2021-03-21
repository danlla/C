#include <stdio.h>
#include <stdlib.h>
#pragma warning( disable : 6031)

void pair_min_numbers(const int* const numbers, const size_t n, int* min1, int* min2)
{
	if (numbers[0] < numbers[1])
	{
		*min1 = numbers[0];
		*min2 = numbers[1];
	}
	else
	{
		*min1 = numbers[1];
		*min2 = numbers[0];
	}
	for (size_t i = 2; i < n; ++i)
	{
		if (numbers[i] < *min2)
			if (numbers[i] < *min1)
			{
				*min2 = *min1;
				*min1 = numbers[i];
			}
			else
				*min2 = numbers[i];
	}
}

int main(void)
{
	size_t n = 0;
	printf("N = ");
	scanf("%zu", &n);
	while (n <= 2)
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

	int min1 = 0;
	int min2 = 0;
	pair_min_numbers(numbers, n, &min1, &min2);
	printf("Min1 = %d\nMin2 = %d",min1, min2);
	free(numbers);
}