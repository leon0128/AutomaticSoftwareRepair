#include <stdio.h>

int main () {
  int x = 0;
  int y = 0;
  int n = 0;
  
  int res = 0;
  
  int ans = 0;
  
  res = scanf("%d", &x);
  res = scanf("%d", &y);
  res = scanf("%d", &n);
  
  if (3*x < y) {
    ans = n*x;
  } else {
    ans = y*(n/3)+x*(n%3);
  }
  
  printf("%d\n", ans);
  return 0;
}