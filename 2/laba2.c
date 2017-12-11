#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
typedef struct elem elem;
struct elem
{
	int value;
	elem* next;
};
typedef struct
{
	elem* head;
}stack;
bool push(stack* st, int a)
{
	elem* tmp = (elem*) malloc(sizeof(elem));
	if(tmp == NULL) return false;
	tmp->value = a;
	tmp->next = st->head;
	st->head = tmp;
	return true;
}
bool pop(stack* st)
{
	elem* tmp = st->head;
	if(tmp == NULL) return false;
	st->head = st->head->next;
	free(tmp);
	tmp = NULL;
	return true;
}
int peek(stack* st)
{
	return st->head->value;
}
int main(int argc, char* argv[])
{
	int const str_len = 32;
	int pipe_1[2];//from user to server
	int pipe_2[2];//from server to user
	pipe(pipe_1);
	pipe(pipe_2);
	pid_t child_pid;
	if((child_pid = fork()) == -1)
	{
		perror("fork");
		exit(-1);
	}
	if(child_pid == 0) // we are in child procces(server)
	{
		close(pipe_1[1]);
		close(pipe_2[0]);
		stack* stck = (stack*) malloc(sizeof(stack)); // creating stack
		stck->head = NULL; // creating stack
		char command[str_len];
		while(1)
		{		
			while(read(pipe_1[0], command, str_len) < 0){}
			//printf("%s\n", command);
			if(!strcmp(command, "peek\n")) 
			{ 
				if(stck->head != NULL)
				{
					int tmp = peek(stck);
					sprintf(command,"%d", tmp); // we can't use itoa func. sprintf() is replacement for itoa()
				}
				else strcpy(command, "empty stack!");
			}
			else if(!strcmp(command, "push\n"))
			{
				strcpy(command, "Enter number...");
				write(pipe_2[1], command, str_len);
				int n;
				printf("wait for input\n");
				while(read(pipe_1[0], command, str_len) < 0){}
				n = atoi(command);
				if(push(stck, n)) strcpy(command, "success!");
				else strcpy(command, "not enough memory!");	
			}
			else if(!strcmp(command, "pop\n"))
			{
				if(pop(stck)) strcpy(command, "success!");
				else strcpy(command, "empty stack!");
			}
			else
			{
				strcpy(command, "Wrong request. Try again!");
			}
			write(pipe_2[1], command, str_len);
		}	
	}
	else // parent process(user)
	{
		close(pipe_1[0]);
		close(pipe_2[1]); 
		while(1)
		{	
			int command[str_len];
			char result[str_len];
			printf("What you want to do?\n");
			printf("pop\n");
			printf("push\n");
			printf("peek\n");
			fgets(command,32, stdin); // enter command
			write(pipe_1[1], command, str_len);
			while(read(pipe_2[0], result, str_len) < 0){}
			if(!strcmp(result,"Enter number..."))
			{

				printf("%s\n", result);
				int n;
				printf("wait for input1\n");
				scanf("%d", &n);
				sprintf(command,"%d", n);
				write(pipe_1[1], command, str_len);
				while(read(pipe_2[0], result, str_len) < 0){}
			}
			printf("%s\n", result);
		}
	}
}