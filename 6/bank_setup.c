#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>
#include "config.h"
int main()
{
    printf("Initialization of banks\n");
    int msgflg = IPC_CREAT | 0666;
    if(msgget((key_t)SBERBANK, msgflg) == -1) perror("SBERBANK\n");
    if(msgget((key_t)VTB, msgflg) == -1) perror("VTB\n");
    if(msgget((key_t)RAIFAZEN, msgflg) == -1) perror("RAIFAZEN\n");
    printf("All banks is opened\n");
    return 0;
}
/*
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
*/