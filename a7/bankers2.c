//Implementation of Algorithm for Deadlock Detection

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P_CAP 10
#define R_CAP 5

void safety();
	
int main() {
	printf("\n__DEADLOCK DETECTION__\n\n");
	
	int n, m, t=0;
	printf("Enter no. of processes: ");
	scanf("%d",&n);
	printf("Enter no. of resources: ");
	scanf("%d",&m);
	
	char pid[n][3], rid[m];
	int alloc[n][m], max[n][m], need[n][m], avail[n][m], total[m], available[m], work[m], finish[n], safety[n];

	printf("\nEnter details of these resources:-\n\n");
	for (int j=0; j<m; j++) {
		printf("Resource name: ");
		scanf(" %c",&rid[j]);
		printf("\tTotal no. of instances: ");
		scanf("%d",&total[j]);
		}

	printf("\n__MENU__\n1. Read data\n2. Print data\n3. Check system state\n4. Exit\n");
	
	int choice = 1;
	do {
		printf("\nEnter choice: ");
		scanf("%d",&choice);
		
		switch (choice) {
			case 1: {
				printf("\nEnter no. of available instances of each resource:-\n\n");
				for (int i=0; i<m; i++) {
					printf("Resource %c: ",rid[i]);
					scanf("%d",&avail[0][i]);
					work[i] = avail[0][i];
					available[i] = avail[0][i];
					}

				printf("\nEnter no. of processes: ");
				scanf("%d",&n);
					
				printf("Enter the details for each process:-\n\n");
				for (int i=0; i<n; i++) {
					printf("Process name: ");
					scanf("%s",pid[i]);
					printf("\tResources allocated: ");
					for (int j=0; j<m; j++) {
						scanf("%d",&alloc[i][j]);
						}
					printf("\tMaximum resources needed: ");
					for (int j=0; j<m; j++) {
						scanf("%d",&max[i][j]);
						}
					for (int j=0; j<m; j++) {
						need[i][j] = max[i][j] - alloc[i][j];
						}

					finish[i] = 0;
					}
				
				break;
				}
				
			case 2: {
				//print in table form
				printf("\nPID\tAllocated\tMaximum\t\tNeed\t\tAvailable\n");
				printf("\t");
				for (int col=1; col<=4; col++) {
					for (int j=0; j<m; j++)
						printf("%c ",rid[j]);
					printf("\t\t");
					}
				printf("\n");
				
				for (int i=0; i<n; i++) {
					printf("%s\t",pid[i]);
					
					for (int j=0; j<m; j++)
						printf("%d ",alloc[i][j]);
					printf("\t\t");
					
					for (int j=0; j<m; j++)
						printf("%d ",max[i][j]);
					printf("\t\t");
					
					for (int j=0; j<m; j++)
						printf("%d ",need[i][j]);
					printf("\t\t");

					if (i==0) {
						for (int j=0; j<m; j++)
							printf("%d ",available[j]);
						}

					printf("\n");
					}
				break;
				}
				
			case 3: {
				//display current status
				if (choice==3) {
					for (int i=0; i<n; i++) {
						for (int j=0; j<m; j++) {
							need[i][j] = max[i][j] - alloc[i][j];
							}
						}
					}
				
				for (int k=0; k<n; k++)
					finish[k] = 0;

				printf("\nChecking the status of the set of processes:- \n");

				int count = n, i = 0, flag = 0;
				while (count > 0) {
					if (finish[i] == 0) {
						int status = 1;
						for (int j=0; j<m; j++)
							if (need[i][j] > work[j]) {
								status = 0;
								break;
								}
						if (status == 1) {
							flag = 1;
							finish[i] = 1;
							safety[n-count] = i;
							count--;
							for (int j=0; j<m; j++) {
								work[j] = work[j] + alloc[i][j];
								avail[i][j] = work[j];
								}
							}
						
						//printing details of the status of each process
						printf("\nPID\tAllocated\t\tNeed\t\tStatus\t\tWork\n");
						printf("%s\t",pid[i]);
						
						for (int j=0; j<m; j++)
							printf("%d ",alloc[i][j]);
						printf("\t\t\t");
						
						for (int j=0; j<m; j++)
							printf("%d ",need[i][j]);
						printf("\t-->   ");

						if (status==1)
							printf("True\t\t");
						else
							printf("False\t\t");
		
						for (int j=0; j<m; j++)
							printf("%d ",work[j]);
		
						printf("\n");
						}
					
					i++;
					
					if (i==n) {
						if (flag==0 && count!=0) {
							printf("\nPossibility of deadlock!\n");
							printf("\nThe following processes may cause the deadlock: \n<");
							for (int k=0; k<n; k++)
								if (finish[k]==0)
									printf("%s ",pid[k]);
							printf("\b>\n");
							break;
							}
						else {
							i=0;
							flag=0;
							}
						}
					}

				if (count > 0)
					break;

				for (int j=0; j<m; j++)
					work[j] = available[j];

				printf("\nSafety sequence:\n<");
				for (int i=0; i<n; i++)
					printf("%s ",pid[safety[i]]);
				printf("\b>\n");
				
				break;
				}
				
			case 4: {
				printf("Exiting...\n");
				exit(0);
				break;
				}

			default: {
				printf("Invalid choice! Enter again...\n");
				}
			}
		} while (choice!=0);
	
	return 0;
	}
