#include <stdio.h>

int main(void){
  int x,y;
  int N;
  int count;
  
  scanf("%d %d %d",&x,&y,&N);
  
 int Q,R;
  Q = N / 3;
  R = N / 3;
  
  count +=  y * Q;
  count += x * R;
  
  printf("%d",count);
  
  return 0;
}
