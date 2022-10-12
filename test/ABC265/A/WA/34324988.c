#include <stdio.h>
int main(void){
  int x=0, y=0, n=0, d=0, c=0;
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