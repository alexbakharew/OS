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
	stack st;
	int fd[2];
	char command[32];
	pipe(fd);
	pid_t child_pid;
	if((child_pid = fork()) == -1)
	{
		perror("fork");
		exit(-1);
	}
	while(1)
	{
		if(child_pid == 0) // truly child procces
		{
			close(fd[0]); // close input side of pipe
			char tmp_str[32];
			read(fd[1], tmp_str, strlen(tmp_str));
			if(tmp_str[1] == 'e')// peek
			{
				printf("%d\n", st.peek());
			}
			else if(tmp_str[1] == 'o') // pop
			{
				st.pop();
			}
			else if(tmp_str[1] == 'u') // push
			{
				int n;
				printf("Enter value\n");
				scanf("%d", &n);
				st.push(n);
			}
			else
			{
				printf("Wrong request. Try again\n");
			}
			//exit(0);
		}
		else // parent process
		{
			printf("What you want to do?\n");
			printf("pop\n");
			printf("push\n");
			printf("peek\n");
			scanf("%s", command); // enter command
			close(fd[1]); // close output side of pipe
			write(fd[0], command, strlen(command));
			//exit(0);
		}
	}
	return 0;
}