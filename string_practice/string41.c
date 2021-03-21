#include <stdio.h>

size_t count_words(const char* str)
{
	size_t count = 0;
	while (*str == ' ')
		++str;
	while (*str)
	{
		while (*str != ' '&&*str!=0)
			++str;
		++count;
		if (*str == 0)
			break;
		while (*str == ' ')
			++str;
	}
	return count;
}

int main(void)
{
	char str[] = "     hi     hi     hi    hi    hi    hi ";
	printf("%zu", count_words(str));
	getchar();
	getchar();
}