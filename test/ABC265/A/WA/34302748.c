#include <stdio.h>

int main(int x, int y ,int N) {
  int a = N/3;
  int b = N - 3*a;
  int Ans = a*y + b*x;
  printf("%d\n", Ans);
}