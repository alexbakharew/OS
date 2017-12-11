#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	printf("%d %d %d %d\n", attempts, tour, score_1, score_2);
	printf("JOPA\n");
	int table[2];
	table[0] = score_1;
	table[1] = score_2;
	srand(time(NULL));
	while(tour != attempts)
	{
		table[0] += 2 + rand() % 12;
		table[1] += 2 + rand() % 12;
		tour++;
	}
	
	int res;
	if(table[0] > table[1])// first player win
	{
		res = 1;
		pthread_exit(&res);
	}
	else if (table[0] < table[1])// second player win
	{
		res = 2;
		pthread_exit(&res);
	}
	else 
	{
		res = 0;
		pthread_exit(&res); // draw
	}
}
void make_analysis(int* table)
{
	int sum = table[0] + table[1] + table[2];
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
	data->attempts = *argv[1];
	data->tour = *argv[2];
	data->score_1 = *argv[3];
	data->score_2 = *argv[4];
	data->experiments = *argv[5];

	pthread_t tid; // идентификатор потока 
  	pthread_attr_t attr; // aтрибуты потока 
  	pthread_attr_init(&attr);
  	int result_table[3]; // w1 w2 d
  	for(int i = 0; i <  data->experiments; i++)
  	{
  		pthread_create(&tid,NULL,&count_chances, (void*)data);
  		void* result;
  		//printf("JOPA\n");
  		pthread_join(tid, &result);
  		int r = *((int*) result);
  		result_table[r]++;
  	}
  	make_analysis(result_table);
  	return 0;
}