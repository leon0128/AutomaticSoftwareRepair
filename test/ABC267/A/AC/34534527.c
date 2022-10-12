#include <stdio.h>
int main() {
  char S[256];
  int ans = 0;
  scanf("%s", S);
  if (S[0] == 'M')ans = 5;
  if (S[0] == 'T' && S[1] == 'u') ans = 4;
  if (S[0] == 'W') ans = 3;
  if (S[0] == 'T' && S[1] == 'h') ans = 2;
  if (S[0] == 'F')ans = 1;
  printf("%d", ans);
  return 0;
}