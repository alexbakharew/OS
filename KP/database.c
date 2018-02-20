#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "database.h"
database* create_list()
{
    database* list = (database*) malloc(sizeof(database));
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}
bool add(database* list, stored_message* msg)
{
    stored_message* tmp = (stored_message*) malloc(sizeof(stored_message));
    if(tmp == NULL) return false;
    tmp = msg;
    filed* fld = (field*) malloc(sizeof(field));
    if(fld == NULL) return false;
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