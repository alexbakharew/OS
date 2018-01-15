#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "config.h"
int main()
{
    /*int msgid = msgget(10, 0666 | IPC_CREAT);
    message* msg_s = (message*) malloc(sizeof(message));
    message* msg_c = (message*) malloc(sizeof(message));
    message* clnt = (message*) malloc(sizeof(message));
    //msg_s->mtype = 1;
    //msg_c->mtype = 1;
    //clnt->mtype = 1;
    msg_s->type = 2;
    msg_c->type = 2;
    clnt->type = 2;
    msgsnd(msgid, msg_s, sizeof(message), IPC_NOWAIT);
    msgsnd(msgid, msg_c, sizeof(message), IPC_NOWAIT); 
    msgsnd(msgid, clnt, sizeof(message), IPC_NOWAIT); 
    free(msg_s);
    free(msg_c);
    free(clnt);
    sleep(3);
    printf("---------------------------\n");
    message* msg_s1 = (message*) malloc(sizeof(message));
    message* msg_c1 = (message*) malloc(sizeof(message));
    message* clnt1 = (message*) malloc(sizeof(message));
    msgrcv(msgid, msg_s1, sizeof(message), 0, 0);
    msgrcv(msgid, msg_c1, sizeof(message), 0, 0);
    msgrcv(msgid, clnt1, sizeof(message), 0, 0);
    */
    char a = 'a';
    if(a == 'a') printf("JOPA\n");
     
    return 0;
}