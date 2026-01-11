#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define STICKS 5

pthread_mutex_t stick[STICKS];
pthread_mutex_t eat_lock = PTHREAD_MUTEX_INITIALIZER;

int pieces = 0;
int eat = 0;

void* table(void *arg){
	int id = *(int*) arg;
	int before = id-1;
	if(id == 0){ 
		before = 4;
	}
	while(1){
		pthread_mutex_lock(&stick[id]);
		
		while(pthread_mutex_trylock(&stick[before]) != 0){
			
			pthread_mutex_unlock(&stick[id]);
			
			sched_yield();
			
			pthread_mutex_lock(&stick[id]);
		}

		pthread_mutex_lock(&eat_lock);
		if(eat >= pieces){
			pthread_mutex_unlock(&eat_lock);
			pthread_mutex_unlock(&stick[id]);
			
			pthread_mutex_unlock(&stick[before]);
		
			break;
		}
		
		eat++;
		printf("\n- [PHILOSOPHER %d] - Ate a piece!\n", id, eat);
		pthread_mutex_unlock(&eat_lock);
		pthread_mutex_unlock(&stick[id]);
		pthread_mutex_unlock(&stick[before]);

		long time_s = random() % (int)1e6;
		usleep(time_s);
	}

}

int main(int argc, char *argv[])
{
	for(int i = 0; i<STICKS; i++){
		pthread_mutex_init(&stick[i], NULL);
	}

	srandom(time(NULL));

	if(argc == 2){
		pieces = atoi(argv[1]);

		pthread_t f[5];
		int id[5];

		for (int i = 0; i < 5; i++){
			id[i] = i; 
			pthread_create(&f[i], NULL, table, &id[i]);
		}

		for (int i = 0; i < 5; i++){
			pthread_join(f[i], NULL);
		}

		printf("\n Eaten pieces: %d\n", eat);
	}
	return 0;
}