#include <stdio.h>
int main (void){
  int N,A[100],i,sum=0;
  scanf("%d",&N);
  for(i=0;i<N;i++){
    scanf("%d",&A[i]);
    sum+=A[i];
  }
  printf("%d",sum);
}