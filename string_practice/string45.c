#include <stdio.h>

size_t length_short_word(const char* str)
{
	size_t current_length = 0;
	size_t length = 0;
	while (*str == ' ')
		++str;
	while (*str)
	{
		current_length = 0;
		while (*str != ' '&&*str != 0)
		{
			++str;
			++current_length;
		}
		if (!length)
			length = current_length;
		if(current_length<length)
			length = current_length;
		if (*str == 0)
			break;
		while (*str == ' ')
			++str;
	}
	return length;
}

int main(void)
{
	char str[] = "Finds the next token in a null-terminated byte string pointed to by str.";
	printf("%zu", length_short_word(str));
	getchar();
	getchar();
}