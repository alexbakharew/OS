#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
int main()
{
    int client_sock;
    client_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK , 0); // create socket
    if(client_sock == -1) 
    {
        printf("Error while creating socket!\n");
        exit(-1);
    }
    struct sockaddr_un server_address; // struct for address of the server
    server_address.sun_family = AF_UNIX; // type of server
    strcpy(server_address.sun_path, server_addr); // copy address of the server(defined in config.h) 

    struct sockaddr_un client_address; // struct for address of the client
    client_address.sun_family = AF_UNIX; //type of client
    char name[14]; 
    printf("Enter your name(less than 13 characters)\n");
    scanf("%s", name);
    strcpy(client_address.sun_path, name);// initialize an unique client

    unlink(name);
    if(bind(client_sock, (struct sockaddr*)&client_address, sizeof(client_address)) == -1) // Binding address to socket
    {
        printf("Error while binding!\n"); 
        exit(-1);
    } 
    // connect to server
    if(connect(client_sock, (struct sockaddr*) &server_address, sizeof(server_address)) != 0) 
    {
        printf("Error while connecting to the server\n");
        exit(-1);
    }
    // now we are ready to work
    char command[2];
    char message[MSG_SIZE];
    while(1)
    {
        printf("What you need?\n");
        printf("m - compose and send message to someone\n");
        printf("r - refresh letter box. May be someone just texted to you?\n");
        printf("q - exit from client\n");
        scanf("%s", command);
        if(strcmp(command, "m") == 0) // write message
        {
            printf("You should compose following text:\n");
            printf("To <reciever>.\\n \n");
            printf("<Your message>\\n \n");
            scanf("%s", message);
            fflush(stdin);
            if(send(client_sock, message, MSG_SIZE, MSG_MORE) > 0) printf("Your message was successfully sent\n");
            else
            {
                printf("Something went wrong. Do you want to send it again? [Y/n]\n");
                perror("send\n");
                //scanf("%s\n", command);
                //send(client_sock, message, MSG_SIZE, 0);
                // TODO
            }
            continue;
        }
        if(strcmp(command, "r") == 0) 
        {
            strcpy(message, "r");
            if(send(client_sock, (void*)message, MSG_SIZE, 0) > -1) printf("Your request was successfully sent\n");
            continue;
        }
        else if(strcmp(command, "q") == 0) exit(0);
        else printf("Undefined command\n");
    }
    return 0;
}