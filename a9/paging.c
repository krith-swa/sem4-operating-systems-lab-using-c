//Program to implement paging technique
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frames {
  int allocated;
  int process;
  int page;
} frames;

typedef struct process {
  int pid;
  int npages;
  int pages[50];
} process;

void init(frames *F, int n) {
  for (int i = 0; i < n; i++) {
    F[i].allocated = 1;
    F[i].process = -1; // allocated but unknown
  }
}

int main() {
  int phymemsize, pagesize, n_frames;
  int pid, psize;
  int np = 0;
  printf("\nPAGING TECHNIQUE\n");
  printf("\nEnter Physical Memory Size (in KB): ");
  scanf("%d", &phymemsize);
  printf("Enter Page Size (in KB): ");
  scanf("%d", &pagesize);
  n_frames = ceil(phymemsize / pagesize);
  frames F[n_frames];
  init(F, n_frames);
  int n, inputfree[50];
  printf("Enter number of free frames: ");
  scanf("%d", &n);
  printf("Enter string of free frames: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &inputfree[i]);
    F[inputfree[i] - 1].allocated = 0;
    F[inputfree[i] - 1].process = -1; // free
  }
  int choice;
  process P[50];
  do {
    printf("\nMENU: \n\t1.Process request\n\t2.Deallocation\n\t3.Page "
           "Table Display\n\t4.Free frame list display\n\t5.Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      // process request
      printf("Enter process requirements\nID: P");
      scanf("%d", &pid);
      printf("Size (in KB): ");
      scanf("%d", &psize);
      int nreqpages = ceil(psize / pagesize);
      if (n > nreqpages) {
        int temp = nreqpages;
        int tempfp[50];

        for (int i = 0; i < n; i++) {
          tempfp[i] = inputfree[i];
        }

        P[np].pid = pid;
        P[np].npages = temp;
        printf("Process is divided into %d pages\n", nreqpages);
        //
        // while (temp > 0)
        for (int i = 0; i < n && temp > 0; i++) {
          // if (F[tempfp[i]-1].allocated == 0)
          //{
          printf("Page %d: Frame %d\n", nreqpages - temp, tempfp[i]);
          P[np].pages[nreqpages - temp] = tempfp[i];
          F[tempfp[i] - 1].allocated = 1;
          F[tempfp[i] - 1].process = pid;
          F[tempfp[i] - 1].page = nreqpages - temp;
          temp--;
          n--;
          // updating process
          P[np].pages[nreqpages - temp] = tempfp[i];
          for (int j = 0; j < n; j++)
            inputfree[j] = inputfree[j + 1];
          //}
        }
        np++;
      } else {
        printf(
            "Unsuccessful. Insufficient free frames available for process.\n");
      }
      break;
    case 2:
      // deallocation
      if (n == n_frames)
        printf("All blocks are free frames.\n");
      else {
        printf("Enter process ID to be deallocated: P");
        scanf("%d", &pid);
        for (int i = 0; i < np; i++) {
          if (P[i].pid == pid) {
            for (int j = 0; j < P[i].npages; j++) {
              inputfree[n] = P[i].pages[j];
              n += 1;
            }
          }
        }
        np--;
        printf("Deallocation successful\n");
      }
      break;
    case 3:
      // pagetable display
      printf("Page Table Display\n");
      for (int i = 0; i < np; i++) {
        printf("Process P%d\n", P[i].pid);
        for (int j = 0; j < P[i].npages; j++) {
          printf("Page %d: Frame %d\n", j, P[i].pages[j]);
        }
      }
      break;
    case 4:
      // free frame display
      printf("Free frames: ");
      for (int i = 0; i < n; i++)
        printf("%d ", inputfree[i]);
      printf("\n");
      break;
    case 5:
      exit(0);
    default:
      printf("Invalid option entered.\n");
      break;
    }
  } while (choice != 5);
  return 0;
}
