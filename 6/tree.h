#include <stdio.h>
#include <stdlib.h>
#include "config.h"
typedef struct
{
    char name[14];
    long int id;
    long long int account;
}client;
typedef struct node node;
struct node
{
    client user;
    node* left;
    node* right;
};
bool add_user(node** nd, message* auth_msg);
bool remove_user(node** nd, message* shutdown_msg);
node* find_user(node** nd, message* msg);