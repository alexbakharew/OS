#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PAGE_SIZE 4096
#define PATTERN_SIZE 128
#define FILE_NAME_SIZE 128
#define LINE_ERROR -101
#define TEST_FILE "tmp.txt"

int fd;
int page_count = 0;
char* page = NULL;
struct stat file_info;
char file_name[FILE_NAME_SIZE];

void print_page()
{
	if(page == NULL) return;
	for(int i = 0; i < PAGE_SIZE; ++i)
	{
		putchar(page[i]);
	}
}
void load_page(size_t n)
{
	if(page != NULL) munmap(page, PAGE_SIZE);
	page = NULL;
	page_count = n;
	if(page_count < 0) page_count = 0;
	page = (char*) mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PAGE_SIZE * page_count);
	if(page == MAP_FAILED) printf("Erorr while mapping memory\n");
	//printf("JOPA\n");	
	//page[PAGE_SIZE] = '\0';
	return;
}
void wc() // amount of lines and chars in whole file
{
	int c_count = 0;
	int l_count = 0;
	size_t i = 0;
	load_page(0); // wc on first page
	while(page[i] != '\0' || page[i] == EOF)
	{
		if(page[i] == '\n') 
		{
			++l_count;
			++c_count;
		}
		else ++c_count;
		++i;
		if(i == PAGE_SIZE) // case, when we catch last char in the page
		{	
			if(page[i - 1] == '\n') 
			{
				++l_count;
				++c_count;
			}
			else ++c_count;
			i = 0;
			++page_count;
			load_page(page_count);
		}
	}
	printf("%d characters, %d lines\n", c_count, l_count);
	return;
}
void change_file()
{
	int temp_fd = open(file_name, O_RDWR | O_APPEND);
	if(temp_fd > 0)
	{
    	stat(file_name, &file_info);
		fd = temp_fd;
		if(page != NULL) munmap(page, PAGE_SIZE);
		page = NULL;
		printf("OK\n");
		return;
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
int find_line(size_t n) // n - num of line
{
	int curr_n = 0;
	size_t i = 0;
	load_page(0);
	while(curr_n != n)
	{
		if(page == NULL || page == MAP_FAILED || page[i] == '\0')// we read all file or page is not loaded
		{
			return LINE_ERROR;
		}
		if(page[i] == '\n')
		{
			++curr_n;
		}
		++i;
		if(i == PAGE_SIZE)// end of page
		{
			if(page[i - 1] == '\n')
			{
				++curr_n;
			}
			++page_count;
			load_page(page_count);
			i = 0;
		}
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
	while(page[i] != '\n')
	{
		//if(page[i] == '\n') break;
		putchar(page[i]);
		++i;
	}	
	printf("\n");
	return;
}

void find_pattern(char* pattern, size_t n) // 2
{
	int i = find_line(n);
	//printf("JOPA\n");
	if(i == LINE_ERROR) 
	{
		printf("No such line!\n");
		return;
	}
	int j = 0;
	while(i != PAGE_SIZE) // until end of line
	{
		if(pattern[j] == '\n' || pattern[j] == '\0' || j == PATTERN_SIZE)
		{
			printf("YES! That is match!\n");
			return;
		}
		if(page[i] == '\n' || page[i] == '\0')
		{
			printf("NO! Can't find this pattern!\n");
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
	size_t j = 0; // iter for pattern
	while(i != PAGE_SIZE && str[j] != '\0' && page[i] != '\0')
	{
		page[i] = str[j];
		++i;
		++j;
	}
	printf("OK\n");
}

bool is_opened() // 4
{
	struct stat temp_file_info;
	if(stat(file_name, &temp_file_info) == 0)
	printf("%lu %lu\n", file_info.st_atime, temp_file_info.st_atime);
	return file_info.st_atime != temp_file_info.st_atime;
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
int main(int argc, char* argv[])
{
	char command[8] = {"default"};
	if(argc == 2 && strcmp(argv[1], "?") == 0) info();
	
	if(argc > 1) //non-interactive mode
	{
		strcpy(file_name, argv[1]);
		change_file();
		strcpy(command, argv[2]);
		//command = argv[2];
	}
	else 
	{
		printf("Enter name of file\n");
		scanf("%s", file_name);
		change_file();
	}
	
	if(argc < 2)printf("What you want to do? For help, hit '?'\n");
	while(1)
	{
		if(strcmp(command, "default") == 0 && argc == 1) scanf("%s", command);
		if(strcmp("quit", command) == 0) break;
		{//scope without func

			if(strcmp(command, "cf") == 0)
			{
				printf("Enter name of file\n");
				scanf("%s", file_name);
				change_file();
			}
			else if(strcmp(command, "wc") == 0) 
			{
				wc();
			}
			else if(strcmp(command, "rl") == 0) 
			{
				size_t n;
				if(argc == 4) 
				{
					n = (size_t)atoi(argv[3]);
				}
				else 
				{
					scanf("%lu", &n);
				}
				read_line(n);
				fflush(stdin);
			}
			else if(strcmp(command, "fp") == 0)
			{
				if(argc == 5)
				{
					find_pattern(argv[3], (size_t) atoi(argv[4]));
				}
				else
				{
					size_t n;
					char pattern[PATTERN_SIZE];
					scanf("%s", pattern);
					scanf("%lu", &n);
					find_pattern(pattern, n);
					fflush(stdin);
				}
			}
			else if(strcmp(command,"ow") == 0)
			{
				if(argc == 5)
				{
					//printf("JOPA\n");
					overwrite((size_t) atoi(argv[3]), argv[4]);
				}
				else
				{
					size_t n;
					char text[PATTERN_SIZE];
					scanf("%lu", &n);
					scanf("%s", text);
					overwrite(n, text);
					fflush(stdin);
				}
			}
			else if(strcmp(command,"io") == 0)
			{
				if(is_opened()) printf("YES\n");
				else printf("NO\n");
			}
			else if(strcmp(command, "?") == 0) info();
			else printf("Wrong command. Try again\n");
			if(argc > 2) return 0;
			printf("\nWhat you want to do? For help, hit '?'\n");
			scanf("%s", command);
			
		}//scope without func

	}
	quit(fd);
	return 0;
}
