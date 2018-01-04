#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PAGE_SIZE 4096
int main()
{
	printf("%d\n", PAGE_SIZE);
    int fd;
    fd = open("test2.txt",O_RDWR | O_APPEND);
	printf("%d\n", fd);
	char* ptr1 = NULL;
	ptr1 = (char*) mmap(0, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0);
	if(ptr1 == MAP_FAILED || ptr1 == NULL)
	{
		perror("Erorr while mapping memory\n");
		return -2;
	}
	int i = 0;
	while(i != 20)
	{
		ptr1[i] = 'Y';
		++i;
	}
	i = 0;
    while(i != PAGE_SIZE)
	{
		putchar(ptr1[i]);
		++i;
	}
	munmap(ptr1, PAGE_SIZE);
    return 0;
}
