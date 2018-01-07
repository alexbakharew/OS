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
    int sock1;
    int sock2;

    sock1 = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock1 == -1) printf("Error while creating socket!\n");

    sock2 = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock2 == -1) printf("Error while creating socket!\n");

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "0123456789123");

    if(bind(sock1, (struct sockaddr*) &address, sizeof(address)) == -1) printf("Error while binding 1!\n");
    //if(bind(sock2, (struct sockaddr*)&address, sizeof(address)) == -1) printf("Error while binding 2!\n");
    
    unlink("0123456789123");
    //unlink("0123456789123");    
    close(sock1);
    close(sock2);
    printf("OK\n");
    return 0;
}