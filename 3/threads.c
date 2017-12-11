#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void* func(void* i)
{
	int a = *((int*) i);
	a+=10;
	printf("value in thread = %d\n", a);
	//printf("I'm thread and this is number %d\n", *(a) + 10);
	pthread_exit(&a);
	//pthread_exit(0);
}
void make_analysis(int* table)
{
	int sum = table[0] + table[1];
	printf("Chances, that first player will win is %2.2f%%\n", (double)table[0] / sum * 100);
	printf("Chances, that second player will win is %2.2f%%\n", (double)table[1] / sum * 100);
}
int main()
{
/*	pthread_t* tid[5]; /* идентификатор потока 
  	pthread_attr_t attr; /* отрибуты потока 
  	pthread_attr_init(&attr);
  	int i = 10;
  	printf("JOPA\n");
  	pthread_create(tid[0],&attr,func,&i);	
  	i++;
  	pthread_create(tid[1],&attr,func,&i);
  	void* DATA; 
  	if (pthread_join(*(tid[0]), &DATA) != 0) 
		{
    		perror("pthread_create() error");
    		return -1;
  		}
		int* r = (int*) DATA;
		printf("%d\n", *r);
		//--------------------------------------------------
		if (pthread_join(*(tid[1]), &DATA) != 0) 
		{
    		perror("pthread_create() error");
    		return -1;
  		}
		r = (int*) DATA;
		printf("%d\n", *r);

  	/*for(int i = 0; i < 10; i++)
  	{
  		pthread_create(&tid,&attr,func,&i);	
  		//printf("JOPA\n");
		if (pthread_join(tid, &DATA) != 0) 
		{
    		perror("pthread_create() error");
    		return -1;
  		}
		int* r = (int*) DATA;
		printf("%d\n", *r);
  	}
	
	//pthread_create(pthread_t* thread, func, 1);*/
	int arr[] = {500, 270};
	make_analysis(arr);
	//double d = (double)5/3;
	//printf("%f\n", d);
	return 0;
}