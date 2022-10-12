#include <stdio.h>
#include <math.h>

int main() {
  
  int n,x,y;
  
  int a,b,c;
  
  int i;
 
 
  scanf("%d %d %d",&x,&y,&n);
  
  if(3*x>=y){
  a=n/3;
  b=n%3;
  
  
  c=a*y+b*x;
  
  printf("%d",c);
  }else{
    
    c=n*x;
    printf("%d",c);
  }
        

  return 0;
}