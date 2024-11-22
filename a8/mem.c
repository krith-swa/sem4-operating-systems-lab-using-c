//Program to implement Memory Management Algorithms - First fit, Best fit and Worst fit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct Memnode {
  int start, end, size, freesize;
	char status[3];
	} mem;

void reset (mem space1[MAX], mem space2[MAX], int n) {
	for (int i=0; i<n; i++) {
		space1[i].start = space2[i].start;
		space1[i].end = space2[i].end;
		space1[i].size = space2[i].size;
		space1[i].freesize = space2[i].freesize;
		strcpy(space1[i].status,space2[i].status);
		}
	}

void shiftl (mem space[MAX], int pos, int n) {
	for (int i=pos; i<n; i++) {
		space[i].start = space[i+1].start;
		space[i].end = space[i+1].end;
		space[i].size = space[i+1].size;
		space[i].freesize = space[i+1].freesize;
		strcpy(space[i].status,space[i+1].status);
		}
	}

void displayfree (mem space[MAX], int numP, int allocs) {
	int n = numP-allocs;
	printf("\n");
	if (n==0) {
		printf("NULL\n");
		return;
		}
	for (int i=0; i<n; i++)
		printf("----------------");
	printf("\n");
	for (int i=0; i<numP; i++) {
		if (strcmp(space[i].status,"H")==0)
			printf("|\t\t%s\t\t|",space[i].status);
		}
	printf("\n");
	for (int i=0; i<n; i++)
		printf("----------------");
	printf("\n");
	for (int i=0; i<numP; i++) {
		if (strcmp(space[i].status,"H")==0)
			printf(" %d\t\t %d",space[i].start,space[i].end);
		}
	printf("\n");
	}

void display (mem space[MAX], int n) {
	printf("\n");
	if (n==0) {
		printf("NULL\n");
		return;
		}
	for (int i=0; i<n; i++)
		printf("----------------");
	printf("\n");
	for (int i=0; i<n; i++) {
		printf("|\t\t%s\t\t|",space[i].status);
		}
	printf("\n");
	for (int i=0; i<n; i++)
		printf("----------------");
	printf("\n");
	for (int i=0; i<n; i++) {
		printf(" %d\t\t %d",space[i].start,space[i].end);
		}
	printf("\n");
	}

int main() {
	printf("\n__MEMORY MANAGEMENT ALGORITHMS__\n");

	mem ph[MAX], free[MAX], alloc[MAX], temp[MAX];

	int numP;
	printf("\nEnter the no. of partitions in memory: ");
	scanf("%d",&numP);

	for (int i=0; i<numP; i++) {
		printf("\nPartition %d: ",i+1);
		printf("\n\tEnter starting address: ");
		scanf("%d",&ph[i].start);
		printf("\tEnter ending address: ");
		scanf("%d",&ph[i].end);
		ph[i].size = ph[i].end - ph[i].start;
		ph[i].freesize = ph[i].size;
		strcpy(ph[i].status,"H");
		}

	reset(temp,ph,numP);
	//displaying physical memory
	printf("\nPhysical memory: \n");
	display(ph,numP);
	//displaying copy of physical memory
	/*printf("\nTemp memory: \n");
	display(temp,numP);*/

	int algoch;
	do {
		printf("\nMemory allocation: \n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit from program\n");
		printf("Enter choice: ");
		scanf("%d",&algoch);

		switch(algoch) {
			case 1: {
				printf("\n__First Fit Memory Allocation Algorithm__\n");
				reset(ph,temp,numP);
				reset(free,ph,numP);
				int acount = 0, pcount = 0, numPh = numP, de = 0;	//counting allocation partitions in memory
				
				int choice;
				do {
					printf("\nMENU: \n1. Allocate\n2. Deallocate\n3. Display\n4. Coalescing of holes\n5. Back to program\n");
					printf("Enter choice: ");
					scanf("%d",&choice);

					switch(choice) {
						case 1: {
							printf("\nAllocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);
							printf("Enter process size: ");
							scanf("%d",&psize);

							for (int i=0; i<numPh; i++) {
								if (psize <= free[i].freesize) {
									alloc[acount].start = free[i].start;
									alloc[acount].end = alloc[acount].start + psize;
									alloc[acount].size = psize;
									alloc[acount].freesize = 0;
									strcpy(alloc[acount].status,pid);
									free[i].start += psize;
									free[i].size -= psize;
									free[i].freesize -= psize;
									//add process to physical memory by separating in partition and shifting other partitions
									ph[pcount].freesize -= psize;
									numPh++;
									pcount = i+acount+de;
									for (int j=numPh-1; j>pcount; j--) {
										ph[j].start = ph[j-1].start;
										ph[j].end = ph[j-1].end;
										ph[j].freesize = ph[j-1].freesize;
										strcpy(ph[j].status,ph[j-1].status);
										}
									ph[pcount+1].start = free[i].start;
									ph[pcount].end = alloc[acount].end;
									ph[pcount].start = alloc[acount].start;
									ph[pcount].freesize = 0;
									strcpy(ph[pcount].status,alloc[acount].status);

									acount++;
									break;
									}
								}

							break;
							}
						
						case 2: {
							printf("\nDeallocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);

							int ploc = -1, floc, aloc = -1;
							for (int i=0; i<numPh; i++) {
								if (strcmp(ph[i].status,pid)==0)
									ploc = i;
								}
							for (int i=0; i<numPh; i++) {
								if (strcmp(alloc[i].status,pid)==0)
									aloc = i;
								}
							floc = ploc-acount+1;
							psize = alloc[aloc].size;

							free[floc].start -= psize;
							free[floc].freesize += psize;

							shiftl(alloc,aloc,acount);
							acount--;

							strcpy(ph[ploc].status,"H");
							ph[ploc].freesize = psize;

							de++;

							break;
							}
						
						case 3: {
							printf("\nDisplaying memory: \n");

							printf("\nAllocated memory: \n");
							display(alloc,acount);
							printf("\nFree memory: \n");
							displayfree(ph,numPh,acount);
							printf("\nPhysical memory: \n");
							display(ph,numPh);

							break;
							}
						
						case 4: {
							printf("\nMerged holes! \n");
							int start = 0, end = 0;
							for (int i=1; i<numPh; i++) {
								if (strcmp(ph[i-1].status,"H")==0) {
									start = ph[i-1].start;
									int j = i;
									while (strcmp(ph[j].status,"H")==0 && j<numPh) {
										shiftl(ph,j-1,numPh-1);
										numPh--;
										}
									end = ph[i].end;
									ph[i-1].start = start;
									ph[i-1].end = end;
									}
								}

							break;
							}

						case 5: {
							printf("\nReturning to main program...\n");
							break;
							}

						default: {
							printf("\nInvalid choice! Try again.\n");
							}
						}
					} while(choice!=5);

				break;
				}

			case 2: {
				printf("\n__Best Fit Memory Allocation Algorithm__\n");
				reset(ph,temp,numP);
				reset(free,ph,numP);
				int acount = 0, pcount = 0, numPh = numP, de = 0;	//counting allocation partitions in memory
				
				int choice;
				do {
					printf("\nMENU: \n1. Allocate\n2. Deallocate\n3. Display\n4. Coalescing of holes\n5. Back to program\n");
					printf("Enter choice: ");
					scanf("%d",&choice);

					switch(choice) {
						case 1: {
							printf("\nAllocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);
							printf("Enter process size: ");
							scanf("%d",&psize);

							int min_idx = 0;
							for (int i=0; i<numP; i++) {
								if (free[i].freesize < free[min_idx].freesize && psize <= free[i].freesize)
									min_idx = i;
								}

							if (psize <= free[min_idx].freesize) {
									alloc[acount].start = free[min_idx].start;
									alloc[acount].end = alloc[acount].start + psize;
									alloc[acount].size = psize;
									alloc[acount].freesize = 0;
									strcpy(alloc[acount].status,pid);
									free[min_idx].start += psize;
									free[min_idx].size -= psize;
									free[min_idx].freesize -= psize;
									//add process to physical memory by separating in partition and shifting other partitions
									numPh++;
									pcount = min_idx+acount+de;
									for (int j=numPh-1; j>pcount; j--) {
										ph[j].start = ph[j-1].start;
										ph[j].end = ph[j-1].end;
										ph[j].freesize = ph[j-1].freesize;
										strcpy(ph[j].status,ph[j-1].status);
										}
									ph[pcount+1].start = free[min_idx].start;
									ph[pcount].end = alloc[acount].end;
									ph[pcount].start = alloc[acount].start;
									ph[pcount].freesize = 0;
									strcpy(ph[pcount].status,alloc[acount].status);

									acount++;
									break;
									}

							break;
							}
						
						case 2: {
							printf("\nDeallocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);

							int ploc = -1, floc, aloc = -1;
							for (int i=0; i<numPh; i++) {
								if (strcmp(ph[i].status,pid)==0)
									ploc = i;
								}
							for (int i=0; i<numPh; i++) {
								if (strcmp(alloc[i].status,pid)==0)
									aloc = i;
								}
							floc = ploc-acount+1;
							psize = alloc[aloc].size;

							free[floc].start -= psize;
							free[floc].freesize += psize;

							shiftl(alloc,aloc,acount);
							acount--;

							strcpy(ph[ploc].status,"H");
							ph[ploc].freesize = psize;

							de++;

							break;
							}
						
						case 3: {
							printf("\nDisplaying memory: \n");

							printf("\nAllocated memory: \n");
							display(alloc,acount);
							printf("\nFree memory: \n");
							displayfree(ph,numPh,acount);
							printf("\nPhysical memory: \n");
							display(ph,numPh);

							break;
							}
						
						case 4: {
							printf("\nMerged holes! \n");
							int start = 0, end = 0;
							for (int i=1; i<numPh; i++) {
								if (strcmp(ph[i-1].status,"H")==0) {
									start = ph[i-1].start;
									int j = i;
									while (strcmp(ph[j].status,"H")==0 && j<numPh) {
										shiftl(ph,j-1,numPh-1);
										numPh--;
										}
									end = ph[i].end;
									ph[i-1].start = start;
									ph[i-1].end = end;
									}
								}

							break;
							}

						case 5: {
							printf("\nReturning to main program...\n");
							break;
							}

						default: {
							printf("\nInvalid choice! Try again.\n");
							}
						}
					} while(choice!=5);

				break;
				}

			case 3: {
				printf("\n__Worst Fit Memory Allocation Algorithm__\n");
				reset(ph,temp,numP);
				reset(free,ph,numP);
				int acount = 0, pcount = 0, numPh = numP, de = 0;	//counting allocation partitions in memory
				
				int choice;
				do {
					printf("\nMENU: \n1. Allocate\n2. Deallocate\n3. Display\n4. Coalescing of holes\n5. Back to program\n");
					printf("Enter choice: ");
					scanf("%d",&choice);

					switch(choice) {
						case 1: {
							printf("\nAllocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);
							printf("Enter process size: ");
							scanf("%d",&psize);

							int max_idx = 0;
							for (int i=0; i<numP; i++) {
								if (free[i].freesize > free[max_idx].freesize && psize <= free[i].freesize)
									max_idx = i;
								}

							if (psize <= free[max_idx].freesize) {
								alloc[acount].start = free[max_idx].start;
								alloc[acount].end = alloc[acount].start + psize;
								alloc[acount].size = psize;
								alloc[acount].freesize = 0;
								strcpy(alloc[acount].status,pid);
								free[max_idx].start += psize;
								free[max_idx].size -= psize;
								free[max_idx].freesize -= psize;
								//add process to physical memory by separating in partition and shifting other partitions
								ph[max_idx].freesize -= psize;
								numPh++;
								pcount = max_idx+acount+de;
								for (int j=numPh-1; j>pcount; j--) {
									ph[j].start = ph[j-1].start;
									ph[j].end = ph[j-1].end;
									ph[j].freesize = ph[j-1].freesize;
									strcpy(ph[j].status,ph[j-1].status);
									}
								ph[pcount+1].start = free[max_idx].start;
								ph[pcount].end = alloc[acount].end;
								ph[pcount].start = alloc[acount].start;
								ph[pcount].freesize = 0;
								strcpy(ph[pcount].status,alloc[acount].status);

								acount++;
								break;
								}

							break;
							}
						
						case 2: {
							printf("\nDeallocating memory: \n");
							char pid[3]; int psize;
							printf("Enter process ID: ");
							scanf("%s",pid);

							int ploc = -1, floc, aloc = -1;
							for (int i=0; i<numPh; i++) {
								if (strcmp(ph[i].status,pid)==0)
									ploc = i;
								}
							for (int i=0; i<numPh; i++) {
								if (strcmp(alloc[i].status,pid)==0)
									aloc = i;
								}
							floc = ploc-acount+1;
							psize = alloc[aloc].size;

							free[floc].start -= psize;
							free[floc].freesize += psize;

							shiftl(alloc,aloc,acount);
							acount--;

							strcpy(ph[ploc].status,"H");
							ph[ploc].freesize = psize;

							de++;

							break;
							}
						
						case 3: {
							printf("\nDisplaying memory: \n");

							printf("\nAllocated memory: \n");
							display(alloc,acount);
							printf("\nFree memory: \n");
							displayfree(ph,numPh,acount);
							printf("\nPhysical memory: \n");
							display(ph,numPh);

							break;
							}
						
						case 4: {
							printf("\nMerged holes! \n");
							int start = 0, end = 0;
							for (int i=1; i<numPh; i++) {
								if (strcmp(ph[i-1].status,"H")==0) {
									start = ph[i-1].start;
									int j = i;
									while (strcmp(ph[j].status,"H")==0 && j<numPh) {
										shiftl(ph,j-1,numPh-1);
										numPh--;
										}
									end = ph[i].end;
									ph[i-1].start = start;
									ph[i-1].end = end;
									}
								}

							break;
							}

						case 5: {
							printf("\nReturning to main program...\n");
							break;
							}

						default: {
							printf("\nInvalid choice! Try again.\n");
							}
						}
					} while(choice!=5);
				
				break;
				}

			case 4: {
				printf("\nExiting the program...\n");
				exit(0);
				break;
				}

			default: {
				printf("\nInvalid choice! Try again.\n");
				}
			}
		
		} while (algoch != 4);
	
	return 0;
	}
