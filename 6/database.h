#include <stdio.h>
#include <stdlib.h>
#include "config.h"
typedef struct
{
    char name[14];
    long int id;
    long long int account;
}client;
typedef struct field field;
struct field
{
    client user;
    node* next;
    node* prev;
};
typedef struct database
{
    field* begin;
    field* end;
    size_t size;
}
database* initialize();
bool add_user(database* list, message* auth_msg);
bool remove_user(database* list, message* shutdown_msg);
field* find_user(database* list, long long int id);