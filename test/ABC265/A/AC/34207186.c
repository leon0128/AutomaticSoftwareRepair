#include<stdio.h>
int main(){
  
  int x, y, n;
  
  scanf("%d %d %d\n", &x, &y, &n);
  
  if( x*3  >  y ){
  	printf("%d\n", (n/3)*y + (n%3)*x );
  } else {
    printf("%d\n", n*x );
  }
  
  return 0;
    
}