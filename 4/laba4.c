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
	if(fd = open("text_file.txt", O_RDONLY | O_WRONLY) == -1)
	{
		perror("Erorr while opening file\n");
		return -1;
	}
	char buffer[256];
	read(fd, buffer, 256);
	printf("%s\n", buffer);
	/*char* ptr = NULL;
	ptr = (char*) mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(ptr == NULL)
	{
		perror("Erorr while mapping memory\n");
		return -2;
	}
	printf("%s\n", ptr);
	munmap(ptr, 4096);*/
	return 0;
}
