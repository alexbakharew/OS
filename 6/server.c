#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>
#include "config.h"
bool connect(int& msgid, int& msgid_cloud )
{
   
    printf("Choose bank, which you want to connect...\n");
    printf("1 - SBERBANK\n");
    printf("2 - VTB\n");
    printf("3 - RAIFAZEN\n");
    int a;
    scanf("%d", &a);
    if(a == 1)
    {
        msgid = msgget((key_t)SBERBANK, IPC_CREAT | 0666);
        msgid_cloud = msgget((key_t)SBERBANK_CLOUD, IPC_CREAT | 0666)
    }
    else if(a == 2)
    {

        msgid = msgget((key_t)VTB, IPC_CREAT | 0666);
        msgid_cloud = msgget((key_t)VTB_CLOUD, IPC_CREAT | 0666)
    }
    else
    {
        msgid = msgget((key_t)RAIFAZEN, IPC_CREAT | 0666);
        msgid_cloud = msget((key_t)RAIFAZEN_CLOUD, IPC_CREAT | 0666);
    }
    if(msgid != -1 && msgid_cloud != -1) 
    {
        printf("successfull connection\n");
        return true;
    }
    else
    {
        printf("Erorr while connection\n");
        return false;
    }
    
}
int main()
{
    printf("SERVER APPLICATION\n");
    int msgid_cloud = 0; // MQ for bank cloud
    int msgid_server = 0;
    if(!connect(msgid_server, msgid_cloud))
    {
        printf("Error while connecting\n");
        exit(-1);
    }
    message* msg = (message*) malloc(sizeof(message));// message buffer
    while(1)
    {
        if(msgrcv(msgid_server, msg, sizeof(message), 0, 0) < 1) continue;
        if(msgsnd(msgid_cloud, msg, sizeof(message), IPC_NOWAIT) == -1)
        {
            perror("msgsnd cloud\n");
            break;
        }
    }
    return 0;
}