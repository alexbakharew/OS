#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void read_str(char* str, size_t str_size)
{
	size_t i = 0;
	while(i != str_size)
	{
		int ch = getchar();
		str[i] = ch;
		if(ch == '\n' || ch == EOF || ch == '\0') return;
	}
}
int main()
{
	int str[32];
	fgets(str,32, stdin);
	printf("%s", str);
	return 0;
}