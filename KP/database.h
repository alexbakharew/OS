#include <stdio.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct field field;
struct field
{
    stored_message* msg;
    field* next;
    field* prev;
};
typedef struct 
{
    field* begin;
    field* end;
    size_t size;
}database;
database* create_list();
bool add(database* list, stored_message* msg);
field* find(database* list, char* name);
bool purge(database* list, field* fld);