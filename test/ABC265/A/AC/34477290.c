#include<stdio.h>

int main(void){
  int X,Y,N;

  scanf("%d %d %d",&X,&Y,&N);
  if((Y/3)>X){
    printf("%d",N*X);
  }
  else{
    printf("%d",Y*(N/3)+X*(N%3));
  }
  return 0;
}