//Program to understand CPU Scheduling processes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAP 10
#define MAX_LEN 3
#define LIM 999

struct Schedule {
	char pID[3];
	int atime, btime, ttime, wtime;
	};

void inputProcesses (struct Schedule[],int);
void burstSort (struct Schedule[],int);
void preemptiveSort (struct Schedule[],int);
void printArray (int[],int);
void calcTimes (struct Schedule[],int);
void printTable (struct Schedule[],int);
void printGantt (struct Schedule[],int);
void printLine();
void printDashLine();
void printShortLine(int);

int main() {
	printf("\n\t\tCPU SCHEDULING ALGORITHMS\n\n");
	
	printf("_____MENU_____\n\n");
	printf("1. FCFS\n2. SJF\n3. SRTF\n\n");
	
	int choice = 1;
	while (choice != 0) {
		printf("\nEnter choice: ");
		scanf("%d",&choice);
		
		switch(choice) {
			case 1: {
				printf("\n__FCFS__\n");
				struct Schedule fcfs[MAX_CAP];
				
				int numP;
				printf("Enter no. of processes: ");
				scanf("%d",&numP);
				
				//get process details
				inputProcesses(fcfs,numP);
				//calculate waiting time and turnabout time
				calcTimes(fcfs,numP);
				//print results
				printTable(fcfs,numP);
				//print gantt chart
				printGantt(fcfs,numP);
				
				break;
				}
				
			case 2: {
				printf("\n__SJF__\n");
				struct Schedule sjf[MAX_CAP];
				
				int numP;
				printf("Enter no. of processes: ");
				scanf("%d",&numP);

				//get process details
				inputProcesses(sjf,numP);
				//sort according to burst time
				burstSort(sjf,numP);
				//calculate wtime and ttime
				calcTimes(sjf,numP);
				//print results
				printTable(sjf,numP);
				//print gantt chart
				printGantt(sjf,numP);
				
				break;
				}
				
			case 3: {
				printf("\n__SRTF__\n");
				struct Schedule srtf[MAX_CAP];
				
				int numP;
				printf("Enter no. of processes: ");
				scanf("%d",&numP);
	
				//get process details
				inputProcesses(srtf,numP);
				//sort according to shortest remaining time
				preemptiveSort(srtf,numP);
				//print results
				printTable(srtf,numP);
				
				break;
				}
			
			case 0: {
				printf("Exiting menu...\n\n");
				exit(0); break;
				}
			
			default: printf("Invalid choice!\n"); break;
			}
		}
	
	return 0;
	}
	
void inputProcesses (struct Schedule sc[], int numP) {
	for (int i=0; i<numP; i++) {
		printf("\nEnter processID: ");
		scanf("%s",sc[i].pID);

		printf("Enter arrival time: ");
		scanf("%d",&sc[i].atime);

		printf("Enter burst time: ");
		scanf("%d",&sc[i].btime);
		}
	}

void calcTimes (struct Schedule sc[], int numP) {
	int wait = 0;
	for (int i=0; i<numP; i++) {
		sc[i].wtime = wait - sc[i].atime;
		if (sc[i].wtime<0) {
			sc[i].wtime = 0;
			wait = 0;
			}
		wait += sc[i].btime;
		sc[i].ttime = sc[i].btime + sc[i].wtime;
		}
	}
	
void printTable (struct Schedule sc[], int numP) {
	printf("\n__No. of processes: %d__\n",numP);
	float wsum = 0, tsum = 0;
	printLine();
	printf("pID\tA_time\tB_time\tW_time\tT_time\n");
	printDashLine();
	for (int i=0; i<numP; i++) {
		printf("%s\t%d\t%d\t%d\t%d\n",sc[i].pID,sc[i].atime,sc[i].btime,sc[i].wtime,sc[i].ttime);
		
		wsum += sc[i].wtime;
		tsum += sc[i].ttime;
		}
	printLine();
	printf("\tAvg. waiting time: %.2f\n",wsum/numP);
	printf("\tAvg. turnaround time: %.2f\n",tsum/numP);
	printLine();
	printf("\n");
	//printGantt(sc,numP);
	}
	
void printGantt (struct Schedule sc[], int numP) {
	printf("\nGantt chart:\n");
	int time = 0;
	printShortLine(numP);
	printf("| |");
	for (int i=0; i<numP; i++) {
		//time += sc[i].btime;
		printf("  %s  | |",sc[i].pID);
		}
	printf("\n");
	printShortLine(numP);
	time = 0;
	printf(" 0 ");
	for (int i=0; i<numP; i++) {
		time += sc[i].btime;
		printf("       %d",time);
		}
	printf("\n");
	printf("\n");
	}
  
void burstSort (struct Schedule sc[], int n) {
	for (int i=0; i<n-1; i++) { 
		int min_idx = i; 
		for (int j=i+1; j<n; j++) 
			if (sc[j].btime < sc[min_idx].btime) 
				min_idx = j; 
  
        	struct Schedule temp = sc[min_idx]; 
		sc[min_idx] = sc[i]; 
		sc[i] = temp;
		} 
	}

void preemptiveSort (struct Schedule sc[], int numP) {
	sc[MAX_CAP-1].btime = LIM;
	int i, smallest, count = 0, newcount = 0, time, context = 0, burst[MAX_CAP];
	//struct Schedule newsc[MAX_CAP];
	
	for (i=0; i<numP; i++)
		burst[i] = sc[i].btime;
	
	for (time=0; count!=numP; time++) {
		smallest = MAX_CAP-1;
		for (i=0; i<numP; i++) {
			if (sc[i].atime<time && sc[i].btime<sc[smallest].btime && sc[i].btime>0) {
				smallest = i;
				/*newsc[newcount] = sc[smallest];
				newsc[newcount].btime = time - context;
				newcount++;
				context = time;*/
				}
			}
		sc[smallest].btime--;
		
		if (sc[smallest].btime == 0) {
			count++;
			sc[smallest].wtime = time - sc[smallest].atime - burst[smallest];
			sc[smallest].ttime = time - sc[smallest].atime;
			}
		}
		
	for (i=0; i<numP; i++)
		sc[i].btime = burst[i];
		
	//printGantt(newsc,newcount);
	}

void printArray (int arr[], int size) { 
	for (int i=0; i < size; i++) 
		printf("%d ",arr[i]); 
	printf("\n"); 
	}

void printLine() {
	printf("___________________________________________\n");
	}
	
void printDashLine() {
	printf("-------------------------------------------\n");
	}

void printShortLine (int n) {
	for (int i=0; i<n; i++)
		printf("----------");
	printf("\n");
	}
