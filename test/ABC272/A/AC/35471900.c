#include<stdio.h>

int main(void){
  int n,i,t,sum=0;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&t);
    sum += t;
  }
  printf("%d",sum);
  return 0;
}