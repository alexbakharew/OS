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
		if(ch == '\n' || ch == EOF) return;
	}
}
int main()
{
	char str[32];
	read_str(str,32);
	printf("%s\n", str);
	return 0;
}