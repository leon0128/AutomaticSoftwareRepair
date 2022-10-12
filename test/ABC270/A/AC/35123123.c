#include <stdio.h>

int main(void){
  int A, B;
  scanf("%d %d", &A, &B);

  int ans = 0;
  if(A >= 4 || B >= 4)
    ans += 4;
  if(A % 2 == 1 || B % 2 == 1)
    ans += 1;
  A /= 2;
  B /= 2;
  if(A % 2 == 1 || B % 2 == 1)
    ans += 2;

  printf("%d", ans);

  return 0;
}