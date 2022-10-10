#include <stdio.h>

int main() {
  int N;
  int ans;
  int A;
  ans = 0;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A);
    ans += A;
  }

  printf("%d", ans);

  return 0;
}