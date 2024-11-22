//Program to implement threads
#include <pthread.h>
#include <stdio.h>

int size;/* this data is shared by the thread(s) */
int arr[50];
float avgresult = 0, minresult = 0, maxresult = 0;

/* threads call this function */
void *avg()
{
  float sum = 0;
  for (int i = 0; i<size; i++)
    sum+=arr[i];
  avgresult = sum/size;
}

void *min()
{
  int minind;
  minind = 0;
  for (int i = 0 ; i<size; i++)
  {
    if (arr[minind] > arr[i])
      minind = i;
  }
  minresult = arr[minind];
}

void *max()
{
  int maxind;
  maxind = 0;
  for (int i = 0 ; i<size; i++)
  {
    if (arr[maxind] < arr[i])
      maxind = i;
  }
  maxresult = arr[maxind]; 
}

int main(int argc, char *argv[])
{
  pthread_t tid1; /* the thread identifier */
  pthread_attr_t attr1;
  pthread_t tid2; /* the thread identifier */
  pthread_attr_t attr2;
  pthread_t tid3; /* the thread identifier */
  pthread_attr_t attr3;
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);
  pthread_attr_init(&attr3);
  //getting input
  printf("Enter size of array: ");
  scanf("%d", &size);
  printf("Enter elements of array: ");
  for (int i = 0 ; i < size; i++)
    scanf("%d", &arr[i]);
  /* create the thread */
  pthread_create(&tid1,&attr1,avg,NULL);
  pthread_create(&tid2,&attr2,min,NULL);
  pthread_create(&tid3,&attr3,max,NULL);
  /* wait for the thread to exit */
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  printf("\n");
  printf("The average value is %.2f\n", avgresult);
  printf("The minimum value is %.2f\n", minresult);
  printf("The maximum value is %.2f\n", maxresult);
}
