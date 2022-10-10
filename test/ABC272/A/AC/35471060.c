#include<stdio.h>
#include<stdlib.h>

int main(){
  int N,A[109];
  scanf("%d",&N);
  for(int i=1;i<=N;i++){
    scanf("%d",&A[i]);
  }
  int sum=0;
  for(int i=1;i<=N;i++){
    sum+=A[i];
  }
  printf("%d",sum);
}