#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int a = 0, b = 0;
	printf("A = ");
	scanf("%d", &a);
	while (a <= 0)
	{
		printf("A = ");
		scanf("%d", &a);
	}
	printf("B = ");
	scanf("%d", &b);
	while (b <= 0)
	{
		printf("B = ");
		scanf("%d", &b);
	}
	while (a >=b )
	{
		a-=b;
	}
	printf("A = %d", a);
}
