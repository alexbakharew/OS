#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <stdbool.h>
char server_addr[] = {"server"};
int main()
{
    int client_sock;
    char name[14]; 
    printf("Enter your name(less than 13 characters)\n");
    scanf("%s", name);

    client_sock = socket(AF_UNIX, SOCK_STREAM, 0); // create socket
    if(client_sock == -1) 
    {
        printf("Error while creating socket!\n");
        exit(-1);
    }
    struct sockaddr_un server_address; // struct for address of the server
    server_address.sun_family = AF_UNIX; // type of server
    strcpy(server_address.sun_path, server_addr); // copy address of the server(defined in config.h) 

    struct sockaddr_un client_address; // struct for address of the client
    client_address.sun_family = AF_UNIX; // type of client
    strcpy(client_address.sun_path, name);// initialize an unique client
    if(unlink(name) == -1) perror("unlink:");
    if((bind(client_sock, (struct sockaddr*)&client_address, sizeof(client_address))) == -1) // Binding address to socket
    {
        perror("bind"); 
        exit(-1);
    }
    // connect to server
    if((connect(client_sock, (struct sockaddr*) &server_address, sizeof(server_address))) == -1) 
    {
        printf("Error while connecting to the server\n");
        exit(-1);
    }
    perror("connect:");
    stored_message* message = (stored_message*) malloc(sizeof(stored_message)); // buffer for message
    strcpy(message->sender, name);// this field is unique and immutable
    while(1)
    {
        char command;
        printf("What you want?\n");
        printf("m - compose and send message to someone\n");
        printf("r - refresh letter box. May be someone just texted to you?\n");
        printf("q - exit from client\n");
        scanf("%s", &command);
        if(command == 'm') // write message
        {
            message->type = _msg; //simple message
            printf("To :");
            scanf("%s", message->recipient);
            printf("Your message: \n");
            scanf("%s", message->msg);

            fflush(stdin); // temp measures
            fflush(stdout); // temp measures

            if((send(client_sock, (void*)message, sizeof(stored_message), 0)) > 1) printf("Your message was successfully sent\n");
            else
            {
                printf("Something went wrong. Do you want to send it again? [Y/n]\n");
                perror("send");
            }
            continue;
        }
        if(command == 'r') //request for mail
        {
            message->type = _request; // request
            if((send(client_sock, (void*)message, sizeof(stored_message), 0)) > 0) printf("Your request was successfully sent\n");
           /* while(1)
            {
                if(recv(client_sock,message, sizeof(stored_message), 0) < 1)
                {
                    printf("waiting for answer...\n");
                    sleep(3);
                    continue;
                }
                else
                {
                    printf("From : %s\n", message->sender);
                    printf("%s\n", message->msg);
                    break;
                }
            }*/
        }
        else if(command == 'q') 
        {
            message->type = _quit;
            send(client_sock, (void*)message, sizeof(stored_message), 0);
            free(message);
            exit(0);
        }
        else printf("Undefined command\n");
    }
    return 0;
}
