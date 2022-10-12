#include <stdio.h>

int main(void) {
  int a, b;
  scanf("%d %d", &a, &b);
  int ans = a | b;
  printf("%d\n", ans);
  return 0;
}
