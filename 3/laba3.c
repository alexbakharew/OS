#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
typedef struct
{
	int attempts;
	int tour;
	int score_1;
	int score_2;
	int experiments;
}variables;
void* count_chances(void* input)
{	
	variables* data = (variables*)input;
	int attempts = data->attempts;
	int tour = data->tour;
	int score_1 = data->score_1;
	int score_2 = data->score_2;
	//printf("%d %d %d %d\n", tour, attempts, score_1, score_2);
	
	int table[2];
	table[0] = score_1;
	table[1] = score_2;
	time_t seed;
	time(&seed);
	srand(seed);
	sleep(1);
	while(tour < attempts)
	{
		table[0] += 2 + rand() % 12;
		table[1] += 2 + rand() % 12;
		tour++;
		printf("1: %d  2: %d tour %d\n", table[0], table[1], tour);
	}
		printf("----------------------------\n");
	
	int* res = (int*) malloc(sizeof(int));
	if(table[0] > table[1])// first player win
	{
		*res = 1;
		//printf("JOPA1\n");
		pthread_exit(res);
	}
	else if (table[0] < table[1])// second player win
	{
		*res = 2;
		//printf("JOPA2\n");
		pthread_exit(res);
	}
	else 
	{
		*res = 0;
		//printf("JOPA0\n");
		pthread_exit(res); // draw
	}
}
void make_analysis(int* table)
{
	int sum = table[0] + table[1] + table[2];
	printf("%d %d %d\n", table[1], table[2], sum);
	printf("Chances, that first player will win is %2.2f%%\n", (double)table[1] / sum * 100);
	printf("Chances, that second player will win is %2.2f%%\n", (double)table[2] / sum * 100);
}
int main(int argc, char* argv[])
{
	if(argc != 6)
	{
		printf("Not enough arguments!\n");
		return -1;
	}
	variables* data = (variables*) malloc(sizeof(variables));
	//printf("%d %d %d\n", *argv[1], *argv[2], *argv[3]);
	data->attempts = atoi(argv[1]);
	data->tour = atoi(argv[2]);
	data->score_1 = atoi(argv[3]);
	data->score_2 = atoi(argv[4]);
	data->experiments = atoi(argv[5]);

	pthread_t tid; // идентификатор потока 
  	pthread_attr_t attr; // aтрибуты потока 
  	pthread_attr_init(&attr);
  	int result_table[3] = {0}; // w1 w2 d
  	for(int i = 0; i <  data->experiments; i++)
  	{
  		pthread_create(&tid,NULL,&count_chances, data);
  		void* result;
  		pthread_join(tid, &result);
  		int r = *((int*)result);
  		if(r == 1) result_table[1]++;
  		else if(r == 2) result_table[2]++;
  	}
  	//printf("table have this view : %d %d %d\n", result_table[0], result_table[1], result_table[2]);
  	make_analysis(result_table);
  	return 0;
}