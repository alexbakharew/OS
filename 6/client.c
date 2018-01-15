#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>
#include "config.h"
int main()
{
    char name[14];
    printf("Enter your name\n");
    scanf("%s", name);
    
    return 0;
}