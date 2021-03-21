#include <stdio.h>
#pragma warning( disable : 6031)

int main()
{
	unsigned k = 0;
	printf("K = ");
	scanf("%u", &k);
	while (k <= 0 || k > 365)
	{
		printf("Invalid value\nK = ");
		scanf("%u", &k);
	}
	char *day[7] = { "Sunday","Monday","Tuesday","Wednesday","Thurday","Friday","Saturday"};
	printf("It's %s", day[k % 7]);
	return 0;
}