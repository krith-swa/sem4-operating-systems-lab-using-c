//Implementation of producer-consumer problem using semaphores

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

#define BUFSIZE 5

struct memory {
    char buffer[BUFSIZE];
    int count;
    sem_t full;
    sem_t empty;
    sem_t mutex;
	};
struct memory *shmptr;

char input_string[BUFSIZE];
int input_index=0;
int c=0;

void producer() {
    do {

		sem_wait(&(shmptr->empty));
		sem_wait(&(shmptr->mutex));
		
		shmptr->buffer[shmptr->count++]=input_string[input_index++];
		shmptr->buffer[shmptr->count]='\0';
		printf("Produced: %c\n",shmptr->buffer[shmptr->count-1]);
		printf("Buffer: %s\n",shmptr->buffer);
		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->full));
		
		sleep(1);
		} while(input_index<strlen(input_string));

    wait(NULL);
    printf("Producer operation completed!\n");
    exit(1);
	}

void consumer() {
    do {

        sem_wait(&(shmptr->full));
        sem_wait(&(shmptr->mutex));

        printf("Consumed: %c\n",shmptr->buffer[0]);
        memmove(shmptr->buffer,shmptr->buffer+1,strlen(shmptr->buffer));
        shmptr->count--;
        c++;

        printf("Buffer: %s\n",shmptr->buffer);
        sem_post(&(shmptr->mutex));
        sem_post(&(shmptr->empty));

        sleep(4);

    	} while(c<strlen(input_string));

    printf("Consumer operation completed!\n");
    exit(1);
	}

int main() {
    int shmid=shmget(IPC_PRIVATE,sizeof(struct memory),IPC_CREAT|0666);
    shmptr=(struct memory *)shmat(shmid,NULL,0);

    sem_init(&(shmptr->full),1,0);
    sem_init(&(shmptr->empty),1,BUFSIZE);
    sem_init(&(shmptr->mutex),1,1);
    shmptr->count=0;
    
    printf("Buffer size: %d\n",BUFSIZE);

    printf("Enter string: ");
    scanf("%s",input_string);

    int pid=fork();

    if(pid==-1)
        printf("Fork error\n");
    else if(pid==0)
        consumer();
    else
        producer();

    shmdt(shmptr);
    shmctl(shmid,IPC_RMID,NULL);
    sem_destroy(&(shmptr->empty));
    sem_destroy(&(shmptr->full));
    sem_destroy(&(shmptr->mutex));
    printf("Complete. Exiting...\n");
}
