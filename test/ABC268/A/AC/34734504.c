#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main(void)
{
  int i, z=1;
  int a[5];
  for(i=0; i<5; i++){
    scanf("%d",&a[i]);
  }
  qsort(a, 5, sizeof(int), compare_int);
  for(i=1; i<5; i++){
    if(a[i]!=a[i-1]){
      z++;
    }
  }
  printf("%d\n", z);
  return 0;
}