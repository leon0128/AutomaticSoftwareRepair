#include <stdio.h>
int main(void){
  int x, y, n, a, b, c, d, e;
  scanf("%d %d %d",&x,&y,&n);
  
  
  c = (n%3)*y + (n/3)*x;
  
  d = n * x;
  if (d >= c){
  	printf("%d",c);
  }else if(d < c){
  	printf("%d",d);
  }
  
  
  return 0;
}