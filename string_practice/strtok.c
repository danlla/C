#include<stdio.h>
#include<string.h>

char* my_strtok(char* str, const char* delim)
{
	static char* context = NULL;
	if (str == NULL)
		str = context;
	if (str == NULL||*str==0)
	{
		return NULL;
	}
	char* tmp = strchr(delim, (int)str[0]);
	size_t i = 0;
	while (tmp != NULL)
	{
		++i;
		tmp = strchr(delim, (int)str[i]);
	}
	size_t j = 0;
	while (tmp == NULL)
	{
		++j;
		tmp = strchr(delim, (int)str[i+j]);
	}
	if (str[i+j] == 0)
		context = NULL;
	else
		context = str + i + j + 1;
	str[i+j] = 0;
	return str+i;
}


int main(void)
{
	char str[] = "    Automatic image recognition is widely used today: There are computer programs that can reliably diagnose skin cancer, navigate self-driving cars, or control robots.";
	const char delim[] = " ,!?.:";
	char* str_changed = my_strtok(str, delim);
	while (str_changed != NULL)
	{
		printf("%s\n", str_changed);
		str_changed = my_strtok(NULL, delim);
	}
	getchar();
	getchar();
}