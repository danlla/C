#include <stdio.h>
#include <string.h>

void substring_between_space(const char* str, char*substring)
{
	while (*str != ' ')
		++str;
	char* begin = ++str;
	while (*str != ' '&&*str != 0)
		++str;
	if (!*str)
		*substring = 0;
	else
		strncpy(substring, begin, str - begin);
}

int main(void)
{
	char str[] = "first_space between_spaces second_space";
	char substr[64] = { 0 };
	substring_between_space(str, substr);
	printf("%s", substr);
	getchar();
	getchar();
}