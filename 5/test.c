#include <dlfcn.h>
#include <stdio.h>

int main()
{
void *handle = dlopen("libdynamic.so",RTLD_LAZY);
int(*fun)(void) = dlsym(handle,"hello");
int x = (*fun)();
dlclose(handle);
printf("Return code: %d\n",x);
return 0;
};