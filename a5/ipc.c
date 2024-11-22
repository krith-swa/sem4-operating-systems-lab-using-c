//Program to implement InterProcess Communication
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//parent writes a char in shared memory which child reads and prints in upper case
void client(int id) {
	char *a;
	a = (char*) shmat(id,NULL,0);
	printf("\nChild -> Uppercase: ");
	for (int i=0; i<strlen(a); i++)
		printf("%c",toupper(a[i]));
	printf("\n");
	shmdt((void*)a);
	}

int main() {
	int pid, id;
	char *c;
	
	id = shmget(IPC_PRIVATE,1024,IPC_CREAT | 00666);
	c = (char*) shmat(id,NULL,0);
	
	printf("Enter string: ");
	scanf("%s",c);
	
	pid = fork();
	
	printf("Parent -> %s",c);
	
	if (pid<0)
		printf("Error occurred");
		
	else if (pid==0) {
		client(id);
		exit(0);
		}
	

	wait(NULL);
	
	printf("\n");

	shmdt((void*)c);
	shmctl(id,IPC_RMID,NULL);
	
	return 0;
	}
