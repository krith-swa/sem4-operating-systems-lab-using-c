//Server side implementation of producer-consumer problem with random number generation

#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>		
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <time.h>

#define BUFSIZE 10

struct memory{
    int buffer[BUFSIZE];
    int count;
    sem_t full;
    sem_t empty;
    sem_t mutex;
    int n;
	};
struct memory *shmptr;

int main() {
    srand(time(0));
    int shmid=shmget(111,sizeof(struct memory),IPC_CREAT|0666);
    shmptr=(struct memory *)shmat(shmid,NULL,0);

    sem_init(&(shmptr->full),1,0);
    sem_init(&(shmptr->empty),1,BUFSIZE);
    sem_init(&(shmptr->mutex),1,1);
    shmptr->count=0;
    
    printf("Number of numbers: ");
    scanf("%d",&(shmptr->n));

    int i=shmptr->n, rnum;
    do {
		sem_wait(&(shmptr->empty));
		sem_wait(&(shmptr->mutex));

		rnum = rand()%100;
		shmptr->buffer[shmptr->count++]=rnum;
		printf("Produced: %d\n",shmptr->buffer[shmptr->count-1]);
		i--;

		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->full));
		sleep(1);
		} while(i>0);
    
    printf("Producer operation completed!\n");
  
    shmdt(shmptr);
    shmctl(shmid,IPC_RMID,NULL);
    sem_destroy(&(shmptr->empty));
    sem_destroy(&(shmptr->full));
    sem_destroy(&(shmptr->mutex));
    printf("__Process completed__\n");
	exit(1);
	}
	

