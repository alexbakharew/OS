#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    time_t t;
    time(&t);
    printf("%lu\n", t);
    sleep(1);
    
    time(&t);
    printf("%lu\n", t);
    sleep(1);
    
    time(&t);
    printf("%lu\n", t);
    sleep(1);
    
    time(&t);
    printf("%lu\n", t);
    sleep(1);

        time(&t);
    printf("%lu\n", t);
    sleep(1);

        time(&t);
    printf("%lu\n", t);
    sleep(1);

        time(&t);
    printf("%lu\n", t);
    sleep(1);

        time(&t);
    printf("%lu\n", t);
    sleep(1);

        time(&t);
    printf("%lu\n", t);
    sleep(1);
    return 0;
}

