#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>
#include "config.h"
int connect()
{
    printf("Choose bank, which you want to connect...\n");
    printf("1 - SBERBANK\n");
    printf("2 - VTB\n");
    printf("3 - RAIFAZEN\n");
    int a;
    scanf("%d", &a);
    int msgid;
    if(a == 1)
    {
        int msgflg = IPC_CREAT | 0666;
        key_t key = (key_t)SBERBANK;
        msgid = msgget(key, msgflg);
    }
    else if(a == 2)
    {
        int msgflg = IPC_CREAT | 0666;
        key_t key = (key_t)VTB;
        msgid = msgget(key, msgflg);
    }
    else
    {
        int msgflg = IPC_CREAT | 0666;
        key_t key = (key_t)RAIFAZEN;
        msgid = msgget(key, msgflg);
    }
    if(msgid != -1)printf("successfull connection\n");
    else printf("Erorr while connection\n");
    return msgid;
}
int main()
{
    int msgid_server = connect(); // connect to bank
    node* root = NULL;
    while(1)
    {
        message* msg = (message*) malloc(sizeof(message));
        msgrcv(msgid_server, msg, sizeof(message), 0, 0);
        if(msg->type == 0)// auth message from client
        {
            if(add_user(&root, msg))
            {
                //successful message
            }
            else
            {
                //unsuccessful message
            }
            tmp_msgid = msgget(msg->sender_id, IPC_CREAT | 0666);
            msgsnd(tmp_msgid, msg, sizeof(message), IPC_NOWAIT);
            continue;
        }
        else if(msg->type == 1)
        {
            
        }
        else if(msg->type == 2)
        {
            
        }
        else if(msg->type == 3)
        {
            
        }
        else if(msg->type == 4)
        {
            
        }
        else
        {

        }
    }


}