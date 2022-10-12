#include <stdio.h>

int main () {
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  
  int res = 0;
  
  res = scanf("%d", &a);
  res = scanf("%d", &b);
  res = scanf("%d", &c);
  res = scanf("%d", &d);
  
  printf("%d\n", (a+b)*(c-d));
  printf("Takahashi\n");
  
  return 0;
}