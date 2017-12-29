#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PAGE_SIZE 4096
#define PATTERN_SIZE 128
#define LINE_ERROR -101

int fd;
int page_count = 0;
char* page = NULL;
void wc() // amount of lines and chars in whole file
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
	char file_name[128];
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
int find_line(size_t n) // n - num of line
{
	int curr_n = 0;
	size_t i = 0;
	load_page(0);
	while(curr_n != n)
	{
		if(page == NULL)// we read all file
		{
			return LINE_ERROR;
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
	int i = find_line(n);
	if(i == LINE_ERROR) 
	{
		printf("No such line!\n");
		return;
	}
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
	int i = find_line(n);
	if(i == LINE_ERROR) 
	{
		printf("No such line!\n");
		return;
	}
	int j = 0;
	while(page[i] != '\n') // until end of line
	{
		if(pattern[j] == '\n' || pattern[j] == '\0' || j == PATTERN_SIZE)
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
	int i = find_line(n);
	if(i == LINE_ERROR) 
	{
		printf("No such line!\n");
		return;
	}
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
	return false;
}

void actions(char* command, int arg_c, char* arg_v) 
{
	if(strcmp(command, "cf") == 0) change_file();
	else if(strcmp(command, "wc") == 0) wc();
	else if(strcmp(command, "rl") == 0) 
	{
		size_t n;
		if(arg_c == 2) n = (size_t)arg_v[2];
		else scanf("%lu", &n);
		read_line(n);
	}
	else if(strcmp(command, "fp") == 0)
	{
		if(arg_c == 3)
		{
			find_pattern(arg_v[2], (size_t)arg_v[3]);
		}
		else
		{
			size_t n;
			char pattern[PATTERN_SIZE];
			scanf("%lu", &n);
			scanf("%s", pattern);
			find_pattern(pattern, n);
		}
	}
	else if(strcmp(command,"ow") == 0)
	{
		if(arg_c == 3)
		{
			overwrite((size_t)arg_v[2], arg_v[3]);
		}
		else
		{
			size_t n;
			char text[PATTERN_SIZE];
			scanf("%lu", &n);
			scanf("%s", text);
			overwrite(n, text);
		}
	}
	else if(strcmp(command,"io") == 0){}
}

void info()
{
	printf("you can proceed following commands:\n");
	printf("cf - change file\n");
	printf("wc - count of strings and characters\n");
	printf("rl 'n' - read line n\n");
	printf("fp 'pattern' 'n' - find pattern in line n\n");
	printf("ow 'n' 'text' - overwrite line n to text\n");
	printf("io - is current file opened in other programms?\n");
	printf("quit - exit from text editor\n");
	return;
}
int main()
{
	if(argc == 3) //non-interactive mode
	{
		fd = open(argv[1], O_RDWR | O_APPEND);
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
		actions(command,argc, argv);
	}
	quit(fd);
	return 0;
}
