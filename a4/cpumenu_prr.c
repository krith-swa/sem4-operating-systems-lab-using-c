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
	int priority;
	};

void inputProcesses (struct Schedule[],int);
void burstSort (struct Schedule[],int);
void prioritySort (struct Schedule[],int);
void roundrobin (struct Schedule[],int,int);
void printArray (int[],int);
void calcTimes (struct Schedule[],int);
void printTable (struct Schedule[],int);
void printTablePrty (struct Schedule[],int);
void printGantt (struct Schedule[],int);
void printLine();
void printDashLine();
void printShortLine(int);

int main() {
	printf("\n\t\tCPU SCHEDULING ALGORITHMS\n\n");
	
	printf("_____MENU_____\n\n");
	printf("1. ROUND ROBIN\n2. PRIORITY\n\n");
	
	int choice = 1;
	while (choice != 0) {
		printf("\nEnter choice: ");
		scanf("%d",&choice);
		
		switch(choice) {
			case 1: {
				printf("\n__ROUND ROBIN__\n");
				/*struct Schedule rr[MAX_CAP];
				
				int numP;
				printf("Enter no. of processes: ");
				scanf("%d",&numP);
				
				int tq;
				printf("Enter time quantum: ");
				scanf("%d",&tq);
				
				//get process details
				for (int i=0; i<numP; i++) {
					printf("\nEnter processID: ");
					scanf("%s",rr[i].pID);

					printf("Enter arrival time: ");
					scanf("%d",&rr[i].atime);

					printf("Enter burst time: ");
					scanf("%d",&rr[i].btime);
					}
				
				
				//calculate waiting time and turnabout time
				roundrobin(rr,numP,tq);
				//print results
				//printTable(rr,numP);
				//print gantt chart
				//printGantt(rr,numP);*/
				
				char pID[10][3], porder[MAX_CAP][3]; int ptime[MAX_CAP], pcount = 0;
				int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];  
				float avg_wt, avg_tat;

				printf("Enter no. of processes: ");
				scanf("%d",&NOP);

				printf("Enter time quantum: ");
				scanf("%d",&quant);
					
				//get process details
				for (i=0; i<NOP; i++) {
					printf("\nEnter processID: ");
					scanf("%s",pID[i]);

					printf("Enter arrival time: ");
					scanf("%d",&at[i]);

					printf("Enter burst time: ");
					scanf("%d",&bt[i]);
					
					temp[i] = bt[i];
					}
				     
				y = NOP;
				
				printf("\n__No. of processes: %d__\n",NOP);
				//float wsum = 0, tsum = 0;
				printLine();
				printf("pID\tA_time\tB_time\tW_time\tT_time\n");
				printDashLine(); 
				for(sum=0, i = 0; y!=0; )  
				{  
				if(temp[i] <= quant && temp[i] > 0)
				{  
				    sum = sum + temp[i];
				    //porder[pcount] = pID[i];
				    strcpy(porder[pcount],pID[i]);
				    ptime[pcount] = sum;
				    pcount++;
				    temp[i] = 0;  
				    count=1;  
				    }     
				    else if(temp[i] > 0)  
				    {  
					temp[i] = temp[i] - quant;  
					sum = sum + quant;
					strcpy(porder[pcount],pID[i]);
					ptime[pcount] = sum;
					pcount++; 
				    }  
				    if(temp[i]==0 && count==1)  
				    {  
					y--;
					printf("%s\t%d\t%d\t%d\t%d\n",pID[i],at[i],bt[i],sum-at[i]-bt[i],sum-at[i]);
					wt = wt+sum-at[i]-bt[i];  
					tat = tat+sum-at[i];  
					count =0;     
				    }  
				    if(i==NOP-1)  
				    {  
					i=0;  
				    }  
				    else if(at[i+1]<=sum)  
				    {  
					i++;  
				    }  
				    else  
				    {  
					i=0;  
				    }  
				}  

				avg_wt = wt * 1.0/NOP;  
				avg_tat = tat * 1.0/NOP;   
				printLine();
				printf("\tAvg. waiting time: %.2f\n",avg_wt);
				printf("\tAvg. turnaround time: %.2f\n",avg_tat);
				printLine();
				printf("\n\n");
				
				
				printf("\nGantt chart:\n");
				printShortLine(pcount);
				printf("| |");
				for (int i=0; i<pcount; i++) {
					printf("  %s  | |",porder[i]);
					}
				printf("\n");
				printShortLine(pcount);
				printf(" 0 ");
				for (int i=0; i<pcount; i++) {
					printf("       %d",ptime[i]);
					}
				printf("\n\n");
				
				break;
				}
				
			case 2: {
				printf("\n__PRIORITY__\n");
				struct Schedule pr[MAX_CAP];
				
				int numP;
				printf("Enter no. of processes: ");
				scanf("%d",&numP);

				//get process details
				inputProcesses(pr,numP);
				//sort according to priority
				prioritySort(pr,numP);
				//print results
				printTablePrty(pr,numP);
				//print gantt chart
				//printGantt(pr,numP);
				
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
		
		printf("Enter priority: ");
		scanf("%d",&sc[i].priority);
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
	
void printTablePrty (struct Schedule sc[], int numP) {
	printf("\n__No. of processes: %d__\n",numP);
	float wsum = 0, tsum = 0;
	printLine();
	printf("pID\tA_time\tB_time\tPrty\tW_time\tT_time\n");
	printDashLine();
	for (int i=0; i<numP; i++) {
		printf("%s\t%d\t%d\t%d\t%d\t%d\n",sc[i].pID,sc[i].atime,sc[i].btime,sc[i].priority,sc[i].wtime,sc[i].ttime);
		
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
	printf("\n\n");
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

void prioritySort (struct Schedule sc[], int numP) {
	sc[MAX_CAP-1].priority = LIM;
	int i, smallest, count = 0, time, burst[MAX_CAP];
	//struct Schedule newsc[MAX_CAP];
	//int newcount = 0, context = 0;
	char porder[MAX_CAP][3]; int ptime[MAX_CAP], pcount = 0;
	
	for (i=0; i<numP; i++)
		burst[i] = sc[i].btime;
	
	for (time=0; count!=numP; time++) {
		smallest = MAX_CAP-1;
		for (i=0; i<numP; i++) {
			if (sc[i].atime<time && sc[i].priority<sc[smallest].priority && sc[i].btime>0) {
				//printf("%s\t",sc[smallest].pID);
				//printf("%s\t\t",sc[i].pID);
				smallest = i;
				/*newsc[newcount] = sc[smallest];
				newsc[newcount].btime = time - context;
				newcount++;
				context = time;*/
				//printf("%s\t",sc[smallest].pID);
				//printf("%s\n",sc[i].pID);
				}
			}
		sc[smallest].btime--;
		
		if (sc[smallest].btime == 0) {
			count++;
			sc[smallest].wtime = time - sc[smallest].atime - burst[smallest];
			sc[smallest].ttime = time - sc[smallest].atime;
			
			//printf("%s\t",sc[smallest].pID);
			//printf("%s\t\n",sc[i].pID);
			//printf("%s\t",sc[i].pID);
			strcpy(porder[pcount],sc[smallest].pID);
			printf("%s\t",porder[pcount]);
			ptime[pcount] = time;
			pcount++;
			}
		
		//printf("%s\t",sc[i].pID);
		//strcpy(porder[pcount],sc[i].pID);
		//printf("%s\t",porder[pcount]);
		//ptime[pcount] = time;
		//pcount++;
		}
		
	for (i=0; i<numP; i++)
		sc[i].btime = burst[i];
		
	//printGantt(newsc,newcount);
	printf("\nGantt chart:\n");
	printShortLine(pcount);
	printf("| |");
	for (int i=0; i<pcount; i++) {
		printf("  %s  | |",porder[i]);
		}
	printf("\n");
	printShortLine(pcount);
	printf(" 0 ");
	for (int i=0; i<pcount; i++) {
		printf("       %d",ptime[i]);
		}
	printf("\n\n");
	
	}
	
void roundrobin (struct Schedule sc[], int numP, int time_quantum) {
	int i, count, time, remain = numP, flag = 0, rt[MAX_CAP];
	//int i, total = 0, counter = 0, limit, x, temp[MAX_CAP];
	printf("here\n");
	
	for (i=0; i<numP; i++) {
		rt[i] = sc[i].btime;
		}
	
	for (time=0, count=0; remain!=0; ) {
		printf("infor\n");
		if (rt[count]<=time_quantum && rt[count]>0) {
			printf("inif\n");
			time += rt[count];
			rt[count] = 0;	
			flag = 1;
			}
		else if (rt[count]>0) {
			printf("inelseif\n");
			rt[count] -= time_quantum;
			time += time_quantum;
			}
		else
			printf("cannot\n");
			
		if (rt[count] && flag==1) {
			printf("inifflag\n");
			remain--;
			sc[count].wtime = time - sc[count].atime - sc[count].btime;
			sc[count].ttime = time - sc[count].atime;
			flag = 0;
			}
		
		if (count == numP-1) {
			printf("inctif\n");
			count = 0;
			}	
		else if (sc[count+1].atime <= time) {
			printf("inctelseif\n");
			count++;
			}
		else {
			printf("inctelse\n");
			count = 0;
			}
		printf("therefor\n");
		}
	
	}

void printArray (int arr[], int size) { 
	for (int i=0; i < size; i++) 
		printf("%d ",arr[i]); 
	printf("\n"); 
	}

void printLine() {
	printf("_______________________________________________\n");
	}
	
void printDashLine() {
	printf("-----------------------------------------------\n");
	}

void printShortLine (int n) {
	for (int i=0; i<n; i++)
		printf("----------");
	printf("\n");
	}
