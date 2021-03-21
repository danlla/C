#include <stdio.h>
#include <string.h>

char* file_extension(char* str)
{
	while (*str)
		++str;
	while (*str != '.')
		--str;
	return ++str;
}

void file_name(char* str, char* name)
{
	while (*str)
		++str;
	while (*str != '.')
		--str;
	char* end = str;
	while (*str != '\\')
		--str;
	++str;
	strncpy(name, str, end - str);
}

int main(void)
{
	char str[] = "C:\\Users\\USER\\Desktop\\Ñ Ñ++\\practice 5\\CmakeLists.txt";
	printf("%s\n", file_extension(str));
	char name[64] = { 0 };
	file_name(str, name);
	printf("%s", name);
	getchar();
	getchar();
}