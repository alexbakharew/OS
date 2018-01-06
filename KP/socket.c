#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/*typedef struct sockaddr
{
    unsigned short sa_family;    // Семейство адресов, AF_xxx
    char sa_data[14];
};*/
int main()
{
    int sock;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock == -1) printf("Error while creating socket!\n");

    struct sockaddr_un address;

    address.sun_family = AF_UNIX;
    //socklen_t
    strcpy(address.sun_path,"addr1");
    if(bind(sock, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding!\n");
    
    close(sock);
    printf("OK\n");
    return 0;
}