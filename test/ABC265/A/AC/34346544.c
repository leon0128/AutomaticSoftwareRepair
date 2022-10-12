#include <stdio.h>

int main() {
  int x, y, n;
  scanf("%d%d%d",&x,&y,&n);

  if (x*3 > y) {
  printf("%d", (n/3)*y + (n%3)*x);
  } 
  else printf("%d",x*n);
  
  return 0;
}