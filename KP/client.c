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
    client_address.sun_family = AF_UNIX; //type of client
    char* name[14]; 
    printf("Enter your name(less than 13 characters)\n");
    scanf("%s", name);
    strcpy(address.sun_path, name);// initialize an unique client

    if(bind(client_sock, (struct sockaddr*)&client_address, sizeof(address)) == -1) // Binding address to socket
    {
        printf("Error while binding!\n"); 
        exit(-1);
    } 
    // connect to server
    if(!connect(int client_sock, (struct sockaddr*) &server_address, sizeof(server_address))) 
    {
        printf("Error while connecting to the server\n");
        exit(-1);
    }
    // now we are ready to work
    char command[2];
    while(1)
    {
        printf("What you need?\n");
        printf("m - compose and send message to someone\n");
        printf("r - refresh letter box. May be someone just texted to you?\n");
        printf("q - exit from client\n");
        scanf("%s", command);
        if(strcmp(command, "m") == 0) // write message
        {

        }
        if(strcmp(command, "r") == 0) // write message
        {

        }
        else if(strcmp(command, "q") == 0) exit(0);
        else printf("Undefined command\n");
    }
    return 0;
}