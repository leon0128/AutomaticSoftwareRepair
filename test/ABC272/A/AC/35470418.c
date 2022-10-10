#include<stdio.h>
int main(){
  int i,n,sum=0,t;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&t);
    sum=sum+t;
  }
  printf("%d",sum);
  return 0;
}