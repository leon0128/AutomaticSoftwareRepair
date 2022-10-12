#include <string.h>
#include <stdio.h>

int n, x;
int main(void) {
  scanf("%d", &n);
  x = n % 998244353;
  x = x + 998244353;
  x = x % 998244353;
  
  printf("%d",x);
  return 0;
}