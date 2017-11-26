#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char const *argv[])
{
	char name[] = "current file";
	char data[] = " This site serves as a helpful resource to forgetful programmers. This site contains an extensive set of code snippets for programmers who have a tendancy to forget the syntax of languages.";
	int fd;
	if((fd = open(name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
	{
		perror(name);
		exit(-1);
	}
	write(fd, data, strlen(data));
	close(fd);
	return 0;
}