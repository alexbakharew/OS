#include<stdio.h>
#include <stdlib.h>
#include "dequeue.h"
#include <dlfcn.h>
int main()
{
    void *library = dlopen("libdq.so",RTLD_LAZY);
    dequeue* dq = (dequeue*) malloc(sizeof(dequeue));
    dq->size = 0;
    size_t(*size)(void) = dlsym(library,"size_of");
    printf("%d\n", (*size)());
    void(*push_front)(void) = dlsym(library, "push_front");
    void(*push_back)(void) = dlsym(library, "push_back");
    long int(*pop_back)(void) = dlsym(library, "pop_back");
    long int(*pop_front)(void) = dlsym(library, "pop_front");

    push_front(dq, 500);
    push_front(dq, 600);
    push_front(dq, 700);
    push_back(dq, 500);
    push_back(dq, 500);
    push_back(dq, 500);
    
    pop_back(dq);
    pop_back(dq);
    pop_back(dq);
    
    
    //free(dq);
    return 0;
}