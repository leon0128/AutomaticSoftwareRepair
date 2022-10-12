#include <stdio.h>

int main() {
  int ans = 0;
  char c1, c2;
  int N;
  scanf("%d", &N);
  ans = N & 0xF;
  if (ans <= 9) {
    c1 = '0' + ans;
  } else {
    c1 = 'A' + ans - 10;
  }
  ans = (N >> 4) & 0xF;
  if (ans <= 9) {
    c2 = '0' + ans;
  } else {
    c2 = 'A' + ans - 10;
  }
  printf("%c%c",c2, c1);
  return 0;
}