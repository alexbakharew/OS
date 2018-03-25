#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, MAX_QUEUE_LEN);
    
    stored_message* message = (stored_message*) malloc(sizeof(stored_message)); // buffer for message

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        recv(sock, message, sizeof(stored_message), 0);

        if(message->type == _msg)
        {
            message->result = true;
        }
        else if(message->type == _request)
        {
            message->result = true;
            strcpy(message->msg, "JOPA!");
            printf("Jopa\n");
        }
        
        send(sock, message, sizeof(stored_message), 0);
        close(sock);
    }
    close(listener);
    
    return 0;
}