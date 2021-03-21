#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

char* convert(int num, int base)
{
	static char buffer[16];
	static char representation[] = "0123456789ABCDEF";
	*(buffer + 15) = 0;
	char* str = buffer + 14;
	do
	{
		*--str = representation[num%base];
		num /= base;
	} while (num != 0);
	return str;
}

size_t my_fprintf(FILE* ostream, char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	char* current = format;
	size_t count_char = 0;
	int i = 0;
	char* s = NULL;
	for (; *current != 0; ++current)
	{
		if (*current == '%')
		{
			switch (*(current + 1))
			{
			case 'c':i = va_arg(arg, int);
					 fputc(i, ostream);
					 ++current;
					 ++count_char;
					 break;
			case 's':s = va_arg(arg, char*);
					  while (*s != 0)
					  {
						  fputc(*s, ostream);
						  ++s;
						  ++count_char;
					  }
					 ++current;
					 break;
			case 'd': i = va_arg(arg, int);
					  if (i < 0)
					  {
						  i = -i;
						  fputc('-', ostream);
					  }
					  s = convert(i, 10);
					  while (*s != 0)
					  {
						  fputc(*s, ostream);
						  ++s;
						  ++count_char;
					  }
					  ++current;
					  break;
			case 'o': i = va_arg(arg,unsigned int);
					  s = convert(i, 8);
					  while (*s != 0)
					  {
					  	  fputc(*s, ostream);
						  ++s;
						  ++count_char;
					  }
					  ++current;
					  break;
			case 'x': i = va_arg(arg, unsigned int);
					  s = convert(i, 16);
					  while (*s != 0)
					  {
						  fputc(*s, ostream);
						  ++s;
						  ++count_char;
					  }
					  ++current;
					  break;
					  
			default: fputc('0', ostream);
			}
		}
		else
		{
			fputc(*current, ostream);
			++count_char;
		}
	}
	va_end(arg);
	return count_char;
}

size_t my_sscanf(char* buffer, char*format, ...)
{
	va_list arg;
	va_start(arg, format);
	char* current = format;
	int* i = NULL;
	char *s = NULL;
	size_t count_reads = 0;
	for (; *current != 0; ++current)
	{
		if (*current == '%')
		{
			switch(*(current+1))
			{
			case 'c': i = va_arg(arg, int*);
					 *i = *buffer;
					 ++current;
					 buffer += 2;
					 ++count_reads;
					 break;
			case 's':s = va_arg(arg, char*);
					 while (*buffer != ' ' && *buffer != 0)
					 {
						 *s = *buffer;
						 ++s;
						 ++buffer;
					 }
					 *s = 0;
					 if(*buffer)
						++buffer;
					 ++current;
					 ++count_reads;
					 break;
			case 'd':i = va_arg(arg, int*);
					 char tmp[11] = { 0 };
					 char* ctmp = tmp;
					 while (*buffer != ' ' && *buffer != 0 && ctmp-tmp!=10)
					 {
						 *ctmp = *buffer;
						 ++ctmp;
						 ++buffer;
					 }
					 *ctmp = 0;
					 *i = atoi(tmp);
					 if (*buffer)
						 ++buffer;
					 ++current;
					 ++count_reads;
					 break;
			}
		}
		else
			++current;
	}
	va_end(arg);
	return count_reads;
}

int main(void)
{
	size_t count_char1 = fprintf(stdout, "std printf:\nhello%d%s%o%x%cend\n", 2534, "hello", 353, 2056,'!');
	size_t count_char2 = my_fprintf(stdout,"my  printf:\nhello%d%s%o%x%cend\n", 2534, "hello",353, 2056,'!');
	printf("count_char: %zu %zu\n", count_char1, count_char2);
	char str1[16];
	char str2[16];
	char str3[16];
	char str4[16];
	char c1 = 0, c2 = 0;
	int i1 = 0;
	int i2 = 0;
	size_t count_reads1 = sscanf("S stroka strochka 2020", "%c%s%s%d", &c1, str1, str2, &i1);
	printf("std sscanf:\n\n%c\n%s\n%s\n%d", c1, str1, str2, i1);
	size_t count_reads2 = my_sscanf("S stroka strochka 2020", "%c%s%s%d", &c2, str3, str4, &i2);
	printf("\nmy sscanf:\n\n%c\n%s\n%s\n%d", c2, str3, str4, i2);
	printf("\ncount reads: %zu %zu", count_reads1, count_reads2);
	getchar();
}