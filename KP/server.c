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
void* create_shared_memory(size_t size) 
{
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, -1, 0);
}
stored_message* find_msg(char* sender, stored_message** shmem, size_t* iter)
{
    stored_message* tmp = NULL;
    size_t i = 0;
    while(i != (*iter))
    {
        tmp = shmem[i * sizeof(stored_message*)];
        if(tmp == NULL) printf("null\n");
        if(strcmp(sender, tmp->recipient) == 0)
        {
            return tmp;
        }
        ++i;
    }
    return NULL;

}
void print_storage(stored_message** shmem, size_t* iter)
{
    stored_message* tmp = NULL;
    size_t i = 0;
    while(i != (*iter))
    {
        tmp = (stored_message*) shmem[i * sizeof(stored_message*)];
        if(tmp == NULL) 
        {
            printf("null\n");
            break;
        }
        printf("recipient is %s\n",(char*)tmp->recipient);
        printf("sender is %s\n", (char*)tmp->sender);
        printf("message is %s\n", (char*)tmp->msg);
        tmp = NULL;
        ++i;
    }
    printf("num of messages is %lu\n", i);
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
    if(bind(serv_sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");
    printf("waiting for clients requests...\n");
    listen(serv_sock, MAX_QUEUE_LEN);
    printf("server was set to listening!\n");
    
    stored_message** shmem = create_shared_memory(512 * sizeof(stored_message*)); // storage for messages
    size_t* iter = create_shared_memory(sizeof(size_t)); // number of stored messages
    *iter = 0;

    
    int temp_sock;
    while(1)
    {
        fflush(stdin);
        fflush(stdout);
        temp_sock = accept(serv_sock, NULL, NULL); // We don't care about client's address
        if (temp_sock < 0) // Waiting for connection
        {
            perror("accept");
            sleep(2);
            continue; 
        }
        pid_t pid = fork();
        if(pid == 0)
        {
            while(1)
            {
                stored_message* message = (stored_message*) malloc(sizeof(stored_message));
                if(recv(temp_sock, message, sizeof(stored_message), 0) < 1) continue;
                if(!message->type) //simple message
                {
                    if(strlen(message->msg) == 0)
                    {
                        printf("exit from client\n");
                        exit(0);
                    }
                    printf("recipient is %s\n",(char*)message->recipient);
                    printf("sender is %s\n", (char*)message->sender);
                    printf("message is %s\n", (char*)message->msg);
                    printf("---------------\n");
                    shmem[(*iter) * sizeof(stored_message*)] = (stored_message*)message;
                    ++(*iter);
                    printf("%lu\n", (*iter));
                }
                else// message type = true
                {
                    printf("in request section\n");
                    //stored_message* tmp_msg;// = (stored_message*) malloc(sizeof(stored_message));
                    //tmp_msg = find_msg(message->sender, shmem, iter);
                    //if(tmp_msg == NULL) printf("no messages for you(\n");
                    //else printf("for you: %s\n", tmp_msg->msg);
                    print_storage(shmem, iter);
                    sleep(1);
                    //free(tmp_msg);
                    //free(message);
                    
                }

            }
            exit(0);
        }
        else continue;

    }
}
