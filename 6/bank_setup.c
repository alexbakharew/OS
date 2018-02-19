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
    if(msgget((key_t)SBERBANK_CLOUD, msgflg) == -1) perror("SBERBANK_CLOUD\n");
    if(msgget((key_t)VTB_CLOUD, msgflg) == -1) perror("VTB_CLOUD\n");
    if(msgget((key_t)RAIFAZEN_CLOUD, msgflg) == -1) perror("RAIFAZEN_CLOUD\n");
    printf("All banks is opened\n");
    return 0;
}  