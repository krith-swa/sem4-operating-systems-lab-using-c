//Client for file transfer application
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct memory {
    char file1[30];
    char file2[30];
    char content[200];
    int status,pid1,pid2;
	};

struct memory* shmptr;

void handler(int signum) {
    printf("interupted\n");
    if(signum==SIGUSR2){
        int fd = open(shmptr->file2,O_WRONLY | O_CREAT,0644);
        write(fd,shmptr->content, strlen(shmptr->content));
        printf("%s saved as %s\n",shmptr->file1,shmptr->file2);
        exit(0);
    	}
	}


int main() {
    int pid = getpid();

    int id=shmget(111,sizeof(struct memory),IPC_CREAT | 0666);
    shmptr = (struct memory*)shmat(id, NULL, 0);
    shmptr->pid2=pid;
    shmptr->status=0;

    char file1[30];
    printf("File name: ");
    scanf("%s",file1);
    strcpy(shmptr->file1,file1);

    char file2[30];
    printf("Save file as: ");
    scanf("%s",file2);
    strcpy(shmptr->file2,file2);

    shmptr->status=1;
    kill(shmptr->pid1,SIGUSR1);

    signal(SIGUSR2, handler);

    while (1) {
        sleep(1);
    	}

    shmdt((void*)shmptr);
    shmctl(id, IPC_RMID, NULL);
	}
