#include <stdio.h>
int main() {
  int n;
  int i;
  int x;
  int sum = 0;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &x);
    sum += x;
  }
  printf("%d", sum);
  return 0;
}