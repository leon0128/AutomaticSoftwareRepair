#include <stdio.h>
int main(void){
  int x, y, n, a, b, c, d, e;
  scanf("%d %d %d",&x,&y,&n);
  
  a = n / 3;
  a = a * x;
  b = n % 3;
  b = b *y;
  c = b + a;
  
  d = n * x;
  if (d >= c){
  	e = c;
  }else if(d < c){
  	e = d;
  }
  
  printf("%d",e);
  
  return 0;
}