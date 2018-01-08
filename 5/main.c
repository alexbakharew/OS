#include<stdio.h>
#include <stdlib.h>
#include "dequeue.h"
int main()
{
    dequeue* dq = (dequeue*) malloc(sizeof(dequeue));
    dq->size = 0;
    printf("%d\n", size_of(dq));
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