#include <stdio.h>
int main(void){
  int x, y, n, d, c;
  scanf("%d %d %d",&x,&y,&n);
  
  
  c = (n/3)*y + (n%3)*x;
  
  d = n * x;
  if (d >= c){
  	printf("%d",c);
  }else if(d < c){
  	printf("%d",d);
  }
  
  
  return 0;
}