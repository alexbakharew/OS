#include <stdio.h>
#include <stdlib.h>
#include "dequeue.h"

extern void push_back(dequeue* dq, long int val)
{
    elem* tmp = (elem*) malloc(sizeof(elem));
    if(tmp == NULL) return;
    tmp->value = val;
    tmp->prev = dq->end;
    tmp->next = NULL;
    dq->end = tmp;
    dq->size++;
    return;
};
extern void push_front(dequeue* dq, long int val)
{
    elem* tmp = (elem*) malloc(sizeof(elem));
    if(tmp == NULL) return;
    tmp->value = val;
    tmp->next = dq->begin;
    tmp->prev = NULL;
    dq->begin = tmp;
    dq->size++;
    return;
};
extern size_t size_of(dequeue* dq)
{
    return dq->size;
};
extern long int pop_front(dequeue* dq)
{
    elem* tmp = dq->begin;
    dq->begin = tmp->next;
    dq->begin->prev = NULL;
    long int val = tmp->value;
    free(tmp);
    tmp = NULL;
    return val;
};
extern long int pop_back(dequeue* dq)
{
    elem* tmp = dq->end;
    dq->end = tmp->prev;
    dq->end->next = NULL;
    long int val = tmp->value;
    free(tmp);
    tmp = NULL;
    return val;
};