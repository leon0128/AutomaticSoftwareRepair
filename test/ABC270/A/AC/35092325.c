#include <stdio.h>

int main() {
  int ans = 0;
  int A, B;
  
  scanf("%d %d", &A, &B);
  ans = A | B;
  printf("%d", ans);
  return 0;
}