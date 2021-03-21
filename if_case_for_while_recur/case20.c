#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int day = 0;
	int month = 0;
	printf("Day: ");
	scanf("%d", &day);
	while (day <= 0 || day > 31)
	{
		printf("Day: ");
		scanf("%d", &day);
	}
	printf("Month: ");
	scanf("%d", &month);
	while (month <= 0 || month > 12)
	{
		printf("Month: ");
		scanf("%d", &month);
	}
	switch (month)
	{
	case 1: if (day >= 20)
				printf("Aquarius");
			else
				printf("Capricorn");
			break;
	case 2: if (day >= 19)
				printf("Pisces");
			else
				printf("Aquarius");
			break;
	case 3: if (day >= 21)
				printf("Aries");
			else
				printf("Pisces");
			break;
	case 4: if (day >= 20)
				printf("Taurus");
			else
				printf("Aries");
			break;
	case 5: if (day >= 20)
				printf("Gemini");
			else
				printf("Taurus");
			break;
	case 6: if (day >= 22)
				printf("Cancer");
			else
				printf("Gemini");
			break;
	case 7: if (day >= 23)
				printf("Leo");
			else
				printf("Cancer");
			break;
	case 8: if (day >= 23)
				printf("Virgo");
			else
				printf("Leo");
			break;
	case 9: if (day >= 23)
				printf("Libra");
			else
				printf("Virgo");
			break;
	case 10: if (day >= 23)
				printf("Scorpio");
			 else
				printf("Libra");
			break;
	case 11: if (day >= 23)
				printf("Sagittarius");
			 else
				printf("Scorpio");
			break;
	case 12: if (day >= 22)
				printf("Capricorn");
			 else
				printf("Sagittarius");
			break;
	default:
		break;
	}
}