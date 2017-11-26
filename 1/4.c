#include <ctime>
#include <iostream>
#include <cstdlib>
int main(int argc, char *argv[])
{
    time_t t;
    time(&t);
    std::cout<<t<<std::endl;
    return 0;
}

