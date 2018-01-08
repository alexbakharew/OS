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
    client_address.sun_family = AF_UNIX; //type of client
    strcpy(client_address.sun_path, name);// initialize an unique client
    if(unlink(name) == -1) perror("unlink:");
    if(bind(client_sock, (struct sockaddr*)&client_address, sizeof(client_address)) == -1) // Binding address to socket
    {
        perror("bind"); 
        exit(-1);
    }
    // connect to server
    if(connect(client_sock, (struct sockaddr*) &server_address, sizeof(server_address)) == -1) 
    {
        printf("Error while connecting to the server\n");
        exit(-1);
    }
    
    while(1)
    {
        char command[2];
        char message[MSG_SIZE];

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
            // (write(client_sock, message, MSG_SIZE) != -1) printf("Your message was successfully sent\n");
            if(send(client_sock, message, MSG_SIZE, 0) != -1) printf("Your message was successfully sent\n");
            else
            {
                printf("Something went wrong. Do you want to send it again? [Y/n]\n");
                perror("send");
            }
            continue;
        }
        if(strcmp(command, "r") == 0) 
        {
            //if(unlink(name) == -1) perror("unlink:");
            //connect_to_server(name, &client_sock);            
            strcpy(message, "r");
            if(send(client_sock, (void*)message, MSG_SIZE, 0) > -1) printf("Your request was successfully sent\n");
            continue;
        }
        else if(strcmp(command, "q") == 0) exit(0);
        else printf("Undefined command\n");
    }
    return 0;
}
