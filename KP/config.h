#define MAX_QUEUE_LEN 256
#define MSG_SIZE 1028
#include <stdbool.h>
char server_addr[] = {"server"};

typedef struct // struct of message
{
    char sender[14];
    char recipient[14];
    char msg[MSG_SIZE];
    bool type; // false - simple message. true - request
} stored_message;