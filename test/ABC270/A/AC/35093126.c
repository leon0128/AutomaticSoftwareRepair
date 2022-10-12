#include <stdio.h>

int main () {
  int a = 0;
  int b = 0;
  
  int res = 0;
  
  res = scanf("%d", &a);
  res = scanf("%d", &b);
  
  printf("%d\n", (a|b));
  return 0;
}