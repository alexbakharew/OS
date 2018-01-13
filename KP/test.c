#include <string.h>
#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
    int array[10] = {0};
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        for(int i = 0; i < 10; i++)
        {
            array[i] = i;
        }
        for(int i = 0; i < 10; i++)
        {
           printf("%d\n", array[i]);
        }
        exit(0);
    }
    if(pid != 0)
    {
        sleep(2);
        for(int i = 0; i < 10; i++)
        {
           printf("%d\n", array[i]);
        }
        exit(0);
    }
    return 0;
}