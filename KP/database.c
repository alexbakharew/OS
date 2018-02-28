#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
database* create_list()
{
    database* list = create_shared_memory(sizeof(database));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}
bool add(database* list, stored_message* msg)
{
    stored_message* tmp = create_shared_memory(sizeof(stored_message));
    if(tmp == NULL) return false;
    tmp = msg;
    field* fld = create_shared_memory(sizeof(field));
    if(fld == NULL) return false;
    fld->msg = msg;
    if(list->size == 0)
    {
        fld->next = NULL;
        fld->prev = NULL;
        list->begin = fld;
        list->end = fld;
        ++list->size;
        return true;
    }
    else
    {
        fld->next = list->begin;
        fld->prev = NULL;
        list->begin->prev = fld;
        list->begin = fld;
        ++list->size;
        return true;
    }
}
field* find(database* list, char* name)
{
    field* tmp = list->begin;
    while(tmp != NULL)
    {
        if(!strcmp(name, tmp->msg->recipient))
        {
            break;
        }
        else
        {
            tmp = tmp->next;
            continue;
        }
    }
    return tmp;
}
void print_list(database* list)
{
    field* tmp = list->begin;
    int i = 0;
    while(i != list->size)
    {
        printf("recipient is %s\n",(char*)tmp->msg->recipient);
        printf("sender is %s\n", (char*)tmp->msg->sender);
        printf("message is %s\n", (char*)tmp->msg->msg);
        tmp = tmp->next;
        ++i;
    }
    return;
}