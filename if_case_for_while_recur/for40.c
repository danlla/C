#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int a = 0;
	int b = 0;
	printf("A = ");
	scanf("%d", &a);
	printf("B = ");
	scanf("%d", &b);
	while (b < a)
	{
		printf("B is more than A\nB = ");
		scanf("%d", &b);
	}
	int tmpa = a;
	for (; a <= b; a++)
	{
		for (int i = 0; i <= a - tmpa; i++)
			printf("%d  ", a);
		printf("\n");
	}
}