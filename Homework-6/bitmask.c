/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <string.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
//#define N 1048576		/* 2^20 or 1 meg elements  */
#define BIN 256
#define MAXBIT 32
#define GROUP 8
#define LST 1
#define BUF 0
#define N 104857600 /* 100 meg elements*/

void selection_sort();

void merge();
void msort_recursive();

void radix_sort();
void int_radix_sort();
void float_radix_sort();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();
void correct();

int n, lst[N], buf[N], flag, floatFlag;

int main(int argc,char **argv) {

  long int del_sec,del_msec;
  struct timeval tv_s,tv_e;
  floatFlag = 0;

  if (argc>1) n = atoi(argv[1]);
  else n = NELM;
  /*
if (argc>2)
{
n = atoi(argv[1]);
float = 1;
}
else if (argc>1)
{
if (argv[1] == "-f")
{

}
}
else
*/
  //printf("n=%d\n",n);
  init_lst(lst,n);
  //print_lst(lst,n);

  gettimeofday(&tv_s, NULL); 
  //selection_sort(lst,n);
  msort_recursive(lst,buf,0,n-1);
  //radix_sort(GROUP);
  gettimeofday(&tv_e, NULL); 

  /****
    PRINT elapsed time in sec and milli secs
  ****/
  del_sec = (tv_e.tv_sec - tv_s.tv_sec);
  del_msec = ((del_sec) * 1000) + ((tv_e.tv_usec - tv_s.tv_usec) / 1000);

  //
  self_check(lst,n-1);
  printf("-Elapsed Time-\n%ld sec\n%ld msec\n",del_sec,del_msec);
  //print_lst(lst,n);
  //float numba = 0.345f;
  //printf("%f\n", numba);
  return 0;
}

void selection_sort(int lst[],int n){
  // fill here
  /* a[0] to a[n-1] is the array to sort */
  int i,j;
  int temp;
  /* advance the position through the entire array */
  /*   (could do j < n-1 because single element is also min element) */
  for (j = 0; j < n-1; j++)
    {
      /* find the min element in the unsorted a[j .. n-1] */

      /* assume the min is the first element */
      int iMin = j;
      /* test against elements after j to find the smallest */
      for (i = j+1; i < n; i++)
	{
	  /* if this element is less, then it is the new minimum */
	  if (lst[i] < lst[iMin])
	    {
	      /* found new minimum; remember its index */
	      iMin = i;
	    }
	}

      if (iMin != j)
	{
	  //swap(a[j], a[iMin]);
	  temp = lst[j];
	  lst[j] = lst[iMin];
	  lst[iMin] = temp;
	}
    }
}

//use recursion
void msort_recursive(int lst[], int buf[], int left, int right){
  if ( left < right )
    {
      int middle = (left + right) / 2;
      msort_recursive(lst,buf,left,middle);
      msort_recursive(lst,buf,middle+1,right);
      merge(lst,buf,left,right);
    }
}

void merge(int lst[], int buf[], int start, int end){
  int middle = (start + end) / 2;
  int temp_index = 0;
  
  int left = start;
  int right = middle + 1;

  while ((left <= middle) && (right <= end))
    {
      if (lst[left] < lst[right])
	{
	  buf[temp_index] = lst[left];
	  temp_index++;
	  left++;
	}
      else
	{
	  buf[temp_index] = lst[right];
	  temp_index++;
	  right++;
	}
    }

  while (left <= middle)
    {
      buf[temp_index] = lst[left];
      temp_index++;
      left++;
    }

  while (right <= end)
    {
      buf[temp_index] = lst[right];
      temp_index++;
      right++;
    }

  for (int i = start; i <= end; i++) (lst[i] = buf[i - start]);
}

void radix_sort(int group) {
  int i;

  /*
    if float flag = true
    then loop through group but call float_radix_sort
    else
    code
   */
  
  // Initialize flag to LST to indicate that lst is the source
  flag = LST;

  
  // Loops through the least significant byte
  for (i=0; i<MAXBIT; i=i+group) {
    int_radix_sort(i,lst,buf,n);
    // sorted numbers must be in lst
    correct();
  }  
}

void int_radix_sort(int idx, int *lst, int *buf, int n) {
  int i, j, k, mask;
  int *src, *dst;
  // Initialize map and count. With all count values set to 0.
  int map[BIN];
  int count[BIN] = { 0 };
  // Set mask to pull 8bits/1byte 4 bits is 0xf
  mask = 0xff;
  // Set src/dst to lst/buf depending on flag
  if ( flag == LST )
    {
      src = lst;
      dst = buf;
      flag = BUF;
    }
  else
    {
      src = buf;
      dst = lst;
      flag = LST;
    }
  /* count */
  for ( i=0; i<n; i++ ) {
    int x = (((*(src+i))>>(GROUP*(idx/8)))&mask);
    count[x]++;
  }
  /* map */
  map[0] = 0;
  for (j=1; j<BIN; j++) (map[j] = (count[j-1] + map[j-1])); 
  /* move */
  for ( k=0; k<n; k++ )
    {
      int y = (((*(src+k))>>(GROUP*(idx/8)))&mask);
      *(dst+(map[y]++)) = *(src+k);
    }
}

void correct(){
  if ( flag == BUF )
    {
      lst == buf;
    }
}

void float_radix_sort(){
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d ",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  //  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  //  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}

void self_check(int *lst,int n) {
  int i, sorted=1;
  
  for ( i=0; i<n-1; i++ )
    {
      if (lst[i] > lst[i+1])
	{
	  
	  sorted = 0;
	  break;
	}
    }
  (sorted) ? printf("sorted\n") : printf("NOT sorted at %d\n",i);
}

/* End of file */
