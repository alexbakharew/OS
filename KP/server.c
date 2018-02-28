#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "database.h"
char server_addr[] = {"server"};


int main()
{
    int serv_sock;
    serv_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK , 0);// server socket
    if(serv_sock == -1) printf("Error while creating socket!\n");
    //--------------------------------------------------------
    /*int* array = create_shared_memory(sizeof(int) * MAX_QUEUE_LEN);
    size_t* it = create_shared_memory(sizeof(size_t));
    *(it) = 0;
    memset(array, 0, MAX_QUEUE_LEN*sizeof(int));*/
    //--------------------------------------------------------
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server");

    unlink(server_addr);
    if(bind(serv_sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");
    printf("waiting for clients requests...\n");
    listen(serv_sock, MAX_QUEUE_LEN);
    printf("server was set to listening!\n");
    
    database* list = create_list();

    while(1)
    {
        sleep(1);
        pid_t pid = fork();
        if(pid == 0)
        {
            int temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address
            if (temp_sock < 0) // Waiting for connection
            {
                perror("accept");
                close(temp_sock);
                exit(0);
            }
            printf("User successfully connected!\n");
        //++(*it);
            stored_message* message = (stored_message*) malloc(sizeof(stored_message));
            while(1)
            {
                if(recv(temp_sock, message, sizeof(stored_message), 0) < 1) 
                {
                    perror("recv ");
                    sleep(1);
                    continue;
                }
                if(message->type == _msg) //simple message
                {
                    if(strlen(message->msg) == 0)
                    {
                        printf("exit from client1\n");

                        exit(0);
                    }
                    if(add(list, message)) printf("Successfull adding!\n");
                    else printf("Message is not added!\n");
                    sleep(1);

                }
                else if(message->type == _request)
                {
                    printf("in request section\n");
                    print_list(list);
                    sleep(1);

                }
                else
                {
                    printf("exit from client2\n");
                    free(message);
                    close(temp_sock);
                    exit(0);
                }

            }
        }
        else continue;

    }
}
