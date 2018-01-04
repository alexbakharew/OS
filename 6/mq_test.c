/* mesg.c */
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>

int main()
{
    int msgid;
    int msgflg = IPC_CREAT | 0666;
    key_t key = 10;
    msgid = msgget(key, msgflg);
    printf("Message queue created with id %d\n",msgid);
    return 0;
}   