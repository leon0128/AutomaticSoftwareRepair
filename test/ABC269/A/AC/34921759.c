#include <stdio.h>

int main() {
  int N;
  int ans = 0;
  int a[5];
  for (int i = 0; i < 4; i++) {
    scanf("%d", &a[i]);
  }
  ans = (a[0]+a[1]) * (a[2] - a[3]);

  printf("%d\n", ans);
  printf("Takahashi");
  return 0;
}