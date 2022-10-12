#include <stdio.h>
#include <stdlib.h>
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

int main() {
  int a[5] = {0};
  int i,r=0;
  for(i=0;i<5;i++) scanf("%d",&a[i]);
  qsort(a,5,sizeof(int),cmp);
  for(i=0;i<5;i++){
    while((i<4) && (a[i]==a[i+1])) i++;
    r++;
  }
  printf("%d\n",r);
  return 0;
}