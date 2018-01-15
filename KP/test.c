#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
void* create_shared_memory(size_t size) {
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
int main()
{
   /* int* iter = create_shared_memory(sizeof(int)); // number of stored messages
    (*iter) = 0;
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        printf("child is here\n");
        for(int i = 0; i < 100; i++)
        {
            if(i == 50)
            {
                printf("half %d\n", *iter);
                sleep(1);
            }
            ++(*iter);
        }
        printf("in child %d\n", (*iter));        
        exit(0);
    }
    if(pid != 0)
    {
        printf("parent is first\n");
        for(int i = 0; i < 100; i++)
        {
                        if(i == 50)
            {
                printf("half %d\n", *iter);
                sleep(1);
            }
            --(*iter);
        }
        printf("in parent %d\n", (*iter));
        exit(0);
    }*/
    int* arr[10];
    int a = 10;
    int* aPtr = &a;
    arr[0] = aPtr;
    printf("%p\n", (arr[0]));
    return 0;
}