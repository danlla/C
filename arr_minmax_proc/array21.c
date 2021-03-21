#include <stdio.h>
#include <stdlib.h>
#pragma warning( disable : 6031)

double avg_range(const double* const numbers, const size_t n, size_t k, size_t l)
{
	double sum = 0;
	int count = l - k+1;
	for (; k <= l; ++k)
		sum += numbers[k-1];
	return sum/count;

}

int main(void)
{
	size_t n = 0;
	printf("N = ");
	scanf("%zu", &n);
	double*numbers = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; ++i)
	{
		printf("%d : ", i);
		scanf("%lf", numbers + i);
	}
	size_t k = 0;
	size_t l = 0;
	printf("K = ");
	scanf("%zu", &k);
	while (k >= n)
	{
		printf("K = ");
		scanf("%zu", &k);
	}
	printf("L = ");
	scanf("%zu", &l);
	while (l <= k || l > n)
	{
		printf("L = ");
		scanf("%zu", &l);
	}

	double sum = avg_range(numbers, n, k, l);
	printf("avg from %zu to %zu = %lf", k, l, sum);
	free(numbers);
}