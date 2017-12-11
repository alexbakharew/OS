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
	int arr[32];
	for(int i = 0; i < 32; i++)
	{
		arr[i] = i;
	}
	arr={0};
		for(int i = 0; i < 32; i++)
	{
		printf("%d\n", arr[i]);
	}
	return 0;
}