#include <stdio.h>

int main() {
  int X, Y, N;
  int ans = 0;
  int cnt = 0;
  scanf("%d %d %d", &X, &Y, &N);
  while(cnt < N) {
    if (N - cnt >= 3 && 3*X > Y) {
      ans += Y;
      cnt+= 3;
    } else {
      ans+= X;
      cnt++;
    }
  }
  printf("%d", ans);
  return 0;
}