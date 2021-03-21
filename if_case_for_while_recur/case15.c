#include <stdio.h>
#pragma warning( disable : 6031)

int main(void)
{
	int suit = 0;
	int denomination = 0;
	printf("Suit: ");
	scanf("%d", &suit);
	while (suit < 1 || suit>4)
	{
		printf("Suit: ");
		scanf("%d", &suit);
	}
	printf("Denomination: ");
	scanf("%d", &denomination);
	while (denomination < 6 || denomination>14)
	{
		printf("Denomination: ");
		scanf("%d", &denomination);
	}
	switch (denomination)
	{
	case 6: printf("the six");
			break;
	case 7: printf("the seven");
			break;
	case 8: printf("the eight");
			break;
	case 9: printf("the nine");
			break;
	case 10:printf("the ten");
			break;
	case 11:printf("the Jack");
			break;
	case 12:printf("the Queen");
			break;
	case 13:printf("the King");
			break;
	case 14:printf("the Ace");
			break;
	default:
		break;
	}
	printf(" of the ");
	switch (suit)
	{
	case 1: printf("spades");
			break;
	case 2: printf("clubs");
			break;
	case 3: printf("diamonds");
			break;
	case 4: printf("hearts");
			break;
	default:
		break;
	}
}