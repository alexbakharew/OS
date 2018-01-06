#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
//int message()
int main()
{
    int serv_sock;
    serv_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(serv_sock == -1) printf("Error while creating socket!\n");

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, server_addr);

    if(bind(serv_sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");

    if(!listen(serv_sock, MAX_QUEUE_LEN)) printf("Error while set server to listening!\n");
    
    int temp_sock; 
    char message[MSG_SIZE];
    while(1)
    {
        temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address
        int recv(int sockfd, void *buf, int len, int flags);
        
        
        int send(int sockfd, const void *msg, int len, int flags);
        close(temp_sock);
    }
}