#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd;
    fd = open("tmp.txt",O_RDWR);
	char* ptr = NULL;
	ptr = (char*) mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(ptr == NULL)
	{
		perror("Erorr while mapping memory\n");
		return -2;
	}
	printf("%s\n", ptr);
	munmap(ptr, 4096);
	return 0;
}