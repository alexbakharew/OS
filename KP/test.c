#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "database.h"
int main()
{
    char name[14]; 
    printf("Enter your name(less than 13 characters)\n");
    scanf("%s", name);
        database* list = create_list();
    while(1)
    {
        char command[2];
        printf("What you want?\n");
        printf("m - compose and send message to someone\n");
        printf("r - refresh letter box. May be someone just texted to you?\n");
        printf("q - exit from client\n");
        scanf("%s", command);
        if(strcmp(command, "m") == 0) // write message
        {
            stored_message* message = (stored_message*) malloc(sizeof(stored_message)); // buffer for message
            message->type = false; //simple message
            strcpy(message->sender, name);
            printf("To :");
            scanf("%s", message->recipient);
            printf("Your message: \n");
            scanf("%s", message->msg);
            fflush(stdin); // temp measures
            fflush(stdout); // temp measures
            add(list, message);

        }
        else
        {
            print_list(list);
        }
    }
}