#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
typedef struct
{
    char name[14];
    char msg[MSG_SIZE];
} stored_message;
int main()
{
    int serv_sock;
    serv_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK , 0);// server socket
    if(serv_sock == -1) printf("Error while creating socket!\n");

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, server_addr);

    unlink(server_addr);
    if(bind(serv_sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");
    printf("waiting for clients requests...\n");
    listen(serv_sock, MAX_QUEUE_LEN);
    printf("server was set to listening!\n");
    
    int temp_sock;
    char message[MSG_SIZE] = {0}; // Buffer for messages
    //stored_message array[MAX_QUEUE_LEN]; // Database
    //size_t size = 0; // Amount of stored messages
    while(1)
    {
        temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address/
        if (temp_sock < 0) // Waiting for connection
        {
            perror("accept");
            sleep(2);
            continue; 
        }
        size_t bytes_read = 0;
        bytes_read = recv(temp_sock, message, MSG_SIZE, 0);
        if(bytes_read < 0) // client is connected. Waiting for message
        {
            close(temp_sock);
            break;
        }
        else // Message is here.
        {
            printf("Server: Your message is: %s\n", (char*)message);
            if(strcmp(message, "r"))
            {
                //
            }
            else
            {
                //determine recipient
                //move to database

            }

            close(temp_sock);
        }
    }
        //int send(int sockfd, const void *msg, int len, int flags);
}