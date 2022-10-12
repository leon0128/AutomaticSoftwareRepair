#include<stdio.h>
#include<math.h>

int main(void){
  
  int x,N,n;
  
  scanf("%d",&x);
  N = x/16;
  n = x%16;
  
  printf("%d%d",N,n);
  
  return 0;
}
