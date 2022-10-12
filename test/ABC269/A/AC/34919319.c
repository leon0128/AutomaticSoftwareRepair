#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define MINIMUM(a, b) (a < b ? a : b)
#define MAXIMUM(a, b) (a > b ? a : b)
#define MAX 998244353
#define POSNUM(a) (a > 0 ? a : a * (-1))

typedef unsigned long long ULL;

typedef struct
{
  int num;
  int suugaku;
  int eigo;
  int goukei;
  int flag;
} juken;

int sort(const void *n1, const void *n2)
{
  if (*(int *)n1 < *(int *)n2)
    return -1;
  else if (*(int *)n1 > *(int *)n2)
    return 1;
  else
    return 0;
}

int ullsort(const void *n1, const void *n2)
{
  if (*(ULL *)n1 < *(ULL *)n2)
    return -1;
  else if (*(ULL *)n1 > *(ULL *)n2)
    return 1;
  else
    return 0;
}


int main(void)
{
  int n,i,j;
  int a,b,c,d;
  scanf("%d %d %d %d",&a,&b,&c,&d);
  printf("%d\n",(a+b)*(c-d));
  printf("Takahashi");
  return 0;
}