#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PAGE_SIZE 4096
#define PATTERN_SIZE 128

int fd;
int page_count = 0;
char* page = NULL;

void wc(int fd) // amount of lines and chars in whole file
{
	int c_count = 0;
	int l_count = 0;
	char symbol;
	while(read(fd, &symbol, sizeof(char)))
	{
		if(symbol == EOF) break;
		else if(symbol == '\n') ++l_count;
		else ++c_count;
	}
	++l_count;
	printf("%d characters, %d lines\n", c_count, l_count);
	return;
}
void change_file()
{
	printf("Enter the name of needed file\n");
	scanf("%s", file_name);
	int temp_fd = open(file_name, O_RDWR | O_APPEND);
	if(temp_fd > 0)
	{
		fd = temp_fd;
		if(page != NULL) munmap(page, PAGE_SIZE);
		page = NULL;
	}
	else perror("unable to load file!\n");
	return;
}
void quit(int fd)
{
	close(fd);
	if(page != NULL) munmap(page, PAGE_SIZE);
	page = NULL;
	printf("goodbye!\n");
	return;
}
void load_page(size_t n)
{
	if(page != NULL) munmap(page, PAGE_SIZE);
	page = NULL;
	page_count = n;
	if(page_count < 0) page_count = 0;
	page = (char*) mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, PAGE_SIZE * page_count);
	page[PAGE_SIZE + 1] = '\0';
	if(page == NULL) perror("Erorr while mapping memory\n");
	return;
}
size_t find_line(size_t n) // n - num of line
{
	int curr_n = 0;
	char ch;
	size_t i = 0;
	load_page(0);
	while(curr_n != n)
	{
		if(page == NULL)// we read all file
		{
			printf("No such line!\n");
			return;
		}
		if(page[i] == '\0')// end of page
		{
			++page_count;
			load_page(page_count);
			i = 0;
		}
		if(page[i] == '\n')
		{
			++curr_n;
		}
		++i;
	}
	return i;
}
void read_line(size_t n) // 1
{
	size_t i = find_line(n);
	while(page[i] != '\n' || page[i] != '\0')
	{
		putchar(page[i]);
		++i;
	}	
	printf("\n");
	return;
}

void find_pattern(char* pattern, size_t n) // 2
{
	int curr_n = 0;
	char ch;
	size_t i = find_line(n);
	int j = 0;
	while(page[i] != '\n') // until end of line
	{
		if(pattern[j] == '\n' || pattern[j] == '\0' || j == PATTREN_SIZE)
		{
			printf("Pattern was found in this line\n");
			return;
		}
		if(page[i] == '\n' || page[i] == '\0')
		{
			printf("There is no pattern in this line\n");
			return;
		}
		if(page[i] == pattern[j])
		{
			++j;
			++i;
			continue;
		}
		else
		{
			++i;
			j = 0;
			continue;
		}
	}
}

void overwrite(size_t n, char* str) // 3 n - num of line
{
	size_t i = find_line(n);
	size_t j = 0;
	while(str[j] != '\n' || str[j] != '\0')
	{
		page[i] = str[j];
		++i;
		++j;
	}
}

bool is_opened() // 4
{

}

void actions(char* command) 
{
	if(strcmp(command, ))
}

void info()
{
	printf("you can proceed following commands:\n");
	printf("cf - change file\n");
	printf("wc - count of strings and characters\n");
	printf("rl 'n' - read line n\n");
	printf("fp 'n' pattern' - find pattren in line n\n");
	printf("ow 'n' 'text' - overwrite line n to text\n");
	printf("io - is current file opened in other programms?\n");
	printf("quit - exit from text editor\n");
	return;
}
int main(int argc, char* argv[])
{
	if(argc == 3) //non-interactive mode
	{
		int fd = open(argv[1], O_RDWR | O_APPEND);
		char* command = argv[2];
		actions(command);
		return 0;
	}
	else if(argv[1] == '?') info();
	change_file();
	char* command;
	while(1)
	{
		printf("What you want to do?\n For help, hit '?'\n");
		scanf("%s", command);
		if(strcmp("quit", command) == 0) break;
		actions(command);
	}
	quit(fd);
	return 0;
}
