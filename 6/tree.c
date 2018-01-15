#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "tree.h"
#include <string.h>
#include <stdbool.h>
bool add_user(node** nd, message* auth_msg)
{
    if((*nd) == NULL)
    {
        node* tmp_nd = (node*) malloc(sizeof(node));
        if(tmp_nd == NULL) return false;
        tmp_nd->client.id = auth_msg->sender_id;
        strcpy(tmp_nd->client.name, auth_msg->name);
        tmp_nd->client.account = auth_msg->value;
        tmp_nd->left = NULL;
        tmp_nd->right = NULL;
        (*nd) = tmp_nd;
        return true;
    }
    else if((*nd)->client.id > auth_msg->sender_id)
    {
        return add_user(&(*nd)->right, auth_msg);
    }
    else if((*nd)->client.id < auth_msg->sender_id)
    {
        return add_user(&(*nd)->left, auth_msg);
    }
    else return false;
}
