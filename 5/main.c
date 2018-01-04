#include<stdio.h>
#include <stdlib.h>
#include "dequeue.h"
int main()
{
    dequeue* dq = (dequeue*) malloc(sizeof(dequeue));
    dq->size = 1450;
    printf("%d\n", size_of(dq));
    free(dq);
    return 0;
}