#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "database.h"
char server_addr[] = {"server"};
typedef struct
{
    int sock;
    database* list;

}args;
void* user(void* a)
{
    printf("User connected\n");
    int sock = (int)((args*) a)->sock;
    database* list = (database*)((args*) a)->list;
    free(a);
    stored_message* msg = (stored_message*) malloc(sizeof(stored_message));
    while(1)
    {    
        printf("tmps is %d\n", sock);
        if((recv(sock, msg, sizeof(stored_message), 0)) <= 0) 
        {
            perror("recv");
            sleep(1);
            continue;
        }
        if(msg->type == _msg) //simple message
        {
            if(strlen(msg->msg) == 0)
            {
                printf("exit from client1\n");
                exit(0);
            }
            if(add(list, msg)) printf("Successfull adding!\n");
            else printf("Message is not added!\n");
            sleep(1);
        }
        else if(msg->type == _request)
        {
            printf("in request section\n");
            print_list(list);
            sleep(1);
        }
        else
        {
            printf("exit from client2\n");
            free(msg);
            close(sock);
            exit(0);
        }
    }
}

int main()
{
    int serv_sock;
    serv_sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK , 0);// server socket
    if(serv_sock == -1) printf("Error while creating socket!\n");
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, server_addr);

    unlink(server_addr);
    if((bind(serv_sock, (struct sockaddr*)&address, sizeof(address))) == -1) printf("Error while binding!\n");
    printf("waiting for clients requests...\n");
    listen(serv_sock, MAX_QUEUE_LEN);
    printf("server was set to listening!\n");
    
    database* list = create_list();
    int temp_sock;
    while(1)
    {
        temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address
        if (temp_sock < 0) 
        {
            perror("accept");
            sleep(1);
            continue; // Waiting for connection
        }
        printf("temp sock is %d\n", temp_sock);
        args* arguments = (args*) malloc(sizeof(args));
        arguments->sock = temp_sock;
        arguments->list = list;

        pthread_t tid; // идентификатор потока 
  	    pthread_attr_t attr; // aтрибуты потока 
  	    pthread_attr_init(&attr);
        pthread_create(&tid, &attr, &user, arguments);
    }
    /*stored_message* msg = (stored_message*) malloc(sizeof(stored_message));
    while(1)
    {    
        int temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address
        
        if (temp_sock < 0) 
        {
            perror("accept");
            sleep(1);
            continue; // Waiting for connection
        }
        while(1)
        {
            if(recv(temp_sock, msg, sizeof(stored_message), 0) < 1) 
            {
                perror("recv");
                sleep(1);
                continue;
            }
            if(msg->type == _msg) //simple message
            {
                if(strlen(msg->msg) == 0)
                {
                    printf("exit from client1\n");
                    break;
                }
                if(add(list, msg)) printf("Successfull adding!\n");
                else printf("Message is not added!\n");
                sleep(1);
                break;
            }
            else if(msg->type == _request)
            {
                printf("in request section\n");
                print_list(list);
                sleep(1);
                break;
            }
        }
    }
    */
}
