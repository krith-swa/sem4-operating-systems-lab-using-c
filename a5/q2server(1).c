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

struct memory{
    char file1[30];
    char file2[30];
    char content[200];
    int status,pid1,pid2;
};

struct memory* shmptr;

void handler(int signum)
{
    if(signum==SIGUSR1){
        printf("Fetching file : %s\n",shmptr->file1);

        int fd = open(shmptr->file1, O_RDONLY);
        

        char content[200];
        
        read(fd,content,200);

        strcpy(shmptr->content,content);

        //printf("here\n");

        shmptr->status =0;

        close(fd);

        kill(shmptr->pid2,SIGUSR2);
        exit(0);
    }
}

int main()
{

    int pid = getpid();
    

    int id=shmget(111,sizeof(struct memory),IPC_CREAT | 0666);
    shmptr = (struct memory*)shmat(id, NULL, 0);
    shmptr->pid1=pid;
    shmptr->status=0;

    signal(SIGUSR1, handler);


    while (1) {
        sleep(1);
    }

    shmdt((void*)shmptr);
    shmctl(id, IPC_RMID, NULL);
    return 0;
}
