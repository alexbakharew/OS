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
    fd = open("tmp.txt",O_RDWR | O_APPEND);
	printf("%d\n", fd);
	char* ptr1 = (char*) mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
	if(ptr1 == MAP_FAILED)
	{
		perror("Erorr while mapping memory\n");
		return -2;
	}
    ptr1[PAGE_SIZE + 1] = '\0';
	printf("%s\n", ptr1);
    return 0;
}