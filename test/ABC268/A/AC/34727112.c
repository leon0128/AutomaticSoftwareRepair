#include <stdio.h>

int s[101];
int main() {
  int ans = 0;
  int A,B,C,D,E;
  for (int i = 0; i < 5; i++) {
    int N;
    scanf("%d", &N);
    s[N]++;
  }
  for (int i = 0; i <= 100; i++) {
    if (s[i])ans++;
  }

  printf("%d", ans);
  return 0;
}