#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
//int message()
typedef struct
{
    char name[14];
    char msg[MSG_SIZE];
} stored_message;
int main()
{
    int serv_sock;
    serv_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK , 0);
    if(serv_sock == -1) printf("Error while creating socket!\n");

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, server_addr);

    unlink(server_addr);
    if(bind(serv_sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");
    printf("waiting for clients requests...\n");
    while(listen(serv_sock, MAX_QUEUE_LEN) != 0) {} // without loop
    printf("server was set to listening!\n");
    
    int temp_sock;
    char message[MSG_SIZE] = {0}; // Buffer for messages
    stored_message array[MAX_QUEUE_LEN]; // Database
    size_t size = 0; // Amount of stored messages
    while(1)
    {
        temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address/
        if (temp_sock == -1) continue; 
        if(recv(temp_sock, message, MSG_SIZE, MSG_MORE) < 0) printf("error while recieve message\n");
        printf("Server: Your message is: %s\n", (char*)message);
        //int send(int sockfd, const void *msg, int len, int flags);
    }
        //close(temp_sock);
}