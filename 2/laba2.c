#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
typedef struct elem elem;
struct elem
{
	int value;
	elem* next;
};

class stack
{
public:
	stack(){};
	~stack(){};
	void push(int);
	void pop();
	int get_size();
	int peek();
	elem* get_head();
	void set_head(elem**);
private:
	elem* head;
	size_t size;
};
void stack::set_head(elem** el)
{
	head = (*el);
	return;
}
elem* stack::get_head()
{
	return head;
}
void stack::push(int a)
{
	elem* tmp = new elem;
	tmp->value = a;
	tmp->next = get_head();
	set_head(&tmp);
	return;
}
void stack::pop()
{
	elem* tmp = get_head();
	set_head(&((get_head())->next));
	delete tmp;
	tmp = NULL;
}
int stack::peek()
{
	return get_head()->value;
}
int main(int argc, char* argv[])
{
	size_t const str_len = 32;
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
		stack stck;
		char command[str_len];
		while(1)
		{		
			read(pipe_1, command, str_len);
			if(command[1] == 'e') // second letter in command
			{ // peek command

			}
			else if(command[1] == 'u')
			{ // push command

			}
			else if(command[1] == 'o')
			{ // pop command

			}
			else
			{
				printf("Wrong request. Try again\n");
			}
		}
	}
	else // parent process(user)
	{
		close(pipe_1[0]);
		close(pipe_2[1]); 
		while(1)
		{	
			int command[str_len];
			int result[str_len];
			printf("What you want to do?\n");
			printf("pop\n");
			printf("push\n");
			printf("peek\n");
			scanf("%s", command); // enter command
			write(pipe_1, command, str_len);
			read(pipe_2, result, str_len);
			printf("%s\n", result);
			//exit(0);
		}
	}
	return 0;
}