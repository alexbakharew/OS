#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <stdio.h>
#include "config.h"
int connect(void)
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
    int msgid = connect(); // connect to bank
    while(1)
    {

    }


}