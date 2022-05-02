#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct
{	
	int position;
	sem_t *forks;
	sem_t *room;
}philospherStruct;

int eatNum = 0;
int phiNum = 0;
void *philosopher(void *phiStruct);
int main(int argc, char *argv[])
{	int i = 0;
	sem_t room; //used to only allow n-1 philosphers into the room
	if (argc != 3)
	{
		printf("invalid arguments\n");
		exit(0);
	}
	//converts args to eatNum and phiNum
	eatNum = atoi(argv[2]);
	phiNum = atoi(argv[1]);
	sem_t forks[phiNum];
	pthread_t philosphers[phiNum];
	sem_init(&room, 0, phiNum-1); //initializes room semaphore
	//initializes fork semaphore array
	for(i=0;i<phiNum;i++)
	{
		//sets set 1 to only allow one philospher to access them
		sem_init(&forks[i],0,1); 
	}
	//initializes philospher threads
	for (i=0;i<phiNum;i++)
	{
		 philospherStruct *phiInstance = malloc(sizeof(philospherStruct));
		 phiInstance->position=i;
		 phiInstance->room=&room;
		 phiInstance->forks=forks;
		 pthread_create(&philosphers[i], NULL, philosopher, (void *)phiInstance);
	}
	
	//run all threads until completion
	for(i=0;i<phiNum;i++)
	{
        pthread_join(philosphers[i], NULL);
    }
	//destroy 
	for(i=0;i<phiNum;i++) 
	{
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);
	 pthread_exit(NULL);
	return 0;
}
void *philosopher(void *phiStruct)
{
	int i;
	philospherStruct instance = *(philospherStruct *)phiStruct;
	for(i=0;i<eatNum;i++)
	{
		printf("Philosopher %d is thinking\n", instance.position+1); //thinks before picking up fork
		sem_wait(instance.room);
		sem_wait(&instance.forks[instance.position]); //waits for first fork
		sem_wait(&instance.forks[(instance.position+1)%phiNum]); //waits for second fork
		printf("Philosopher %d is eating\n", instance.position+1);
		sem_post(&instance.forks[(instance.position+1)%phiNum]); //release second fork
		sem_post(&instance.forks[instance.position]); // release first fork	
		sem_post(instance.room); 
	}
	printf("Philosopher %d is thinking\n", instance.position+1);
	pthread_exit(NULL);

}
