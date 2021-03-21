#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int k = 0;
	printf("K = ");
	scanf("%d", &k);
	int num = 0, index = 0, res = 0;
	do
	{
		printf("X = ");
		scanf("%d", &num);
		if (num > k)
		{
			res = index+1;
			break;
		}
		++index;
	} while (num != 0);
	printf("index = %d", res);
}
