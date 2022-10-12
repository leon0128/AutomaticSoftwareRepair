#include<stdio.h>
#include<stdlib.h>

int main(void)
{
  int data[101];
  int t;
  int count=0;
  for(int i=0;i<101;i++){
    data[i]=0;
  }
  for(int i=0;i<5;i++){
    scanf("%d ",&t);
    data[t]++;
    if(data[t]<2){
      count++;
    }
  }
  printf("%d",count);
  

  return 0;
}