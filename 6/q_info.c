#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int qid;
    struct msqid_ds qstatus;
    qid=msgget((key_t)atoi(argv[1]),IPC_CREAT);
    if(qid==-1){
	perror("msgget failed");
	exit(1);
    }
    if(msgctl(qid,IPC_STAT,&qstatus)<0){
	perror("msgctl failed");
	exit(1);
    }
    printf("Real user id of the queue creator: %d\n",qstatus.msg_perm.cuid);
    printf("Real group id of the queue creator: %d\n",qstatus.msg_perm.cgid);

    printf("Effective user id of the queue creator: %d\n",qstatus.msg_perm.uid);
    printf("Effective group id of the queue creator: %d\n",qstatus.msg_perm.gid);
    printf("Permissions: %d\n",qstatus.msg_perm.mode);
    printf("Message queue id: %d\n",qid);
    printf("%lu message(s) on queue\n",qstatus.msg_qnum);
    printf("Last message sent by process :%3d at %s \n",qstatus.msg_lspid,ctime(& (qstatus.msg_stime)));

    printf("Last message received by process :%3d at %s \n",qstatus.msg_lrpid,ctime(& (qstatus.msg_rtime)));
    printf("Current number of bytes on queue %lu\n",qstatus.msg_cbytes);
    printf("Maximum number of bytes allowed on the queue%lu\n",qstatus.msg_qbytes);
    return 0;
}   