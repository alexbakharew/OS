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
	/*char* ptr1 = NULL;
	ptr1 = (char*) mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
	if(ptr1 == NULL)
	{
		perror("Erorr while mapping memory\n");
		return -2;
	}
    ptr1[4097] = '\0';*/
	char ptr2[256];
    //ptr2 = (char*) mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, PAGE_SIZE);
	if(ptr2 == NULL)
	{
	//	perror("Erorr while mapping memory\n");
	//	return -2;
	}   
    //ptr2[4097] = '\0';
     
    //printf("%s",buff);
	//printf("%s\n", ptr1);
	//munmap(ptr1, PAGE_SIZE);
    //ptr1 = NULL;
	//printf("%s\n", ptr2);
	//munmap(ptr2, PAGE_SIZE);
	scanf("%s", ptr2);
	//scanf("%s\n", ptr2);    
    printf("%s\n", ptr2);
    return 0;
}