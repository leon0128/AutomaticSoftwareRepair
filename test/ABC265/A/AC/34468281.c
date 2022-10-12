#include <stdio.h>

int main() {
  int x, y, n;
  scanf("%d%d%d",&x,&y,&n);
  
  if(n==1||n==2){
    printf("%d",n*x);
  }
  else if (x*3 > y) {
  printf("%d", (n/3)*y + (n%3)*x);
  } 
  else printf("%d",x*n);
  
  return 0;
}