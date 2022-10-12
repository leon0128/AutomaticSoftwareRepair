#include <stdio.h>
int main(void){
  int X,Y,N;
  int sum;
  scanf("%d %d %d",&X,&Y,&N);
  if(3*X>Y){
  sum=Y*(N/3)+X*(N%3);
  }else{sum=X*N;};
  printf("%d",sum);
  return 0;
}