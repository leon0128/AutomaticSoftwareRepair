#include <stdio.h>

int main(void)
{
  int y, p, q, r;
  scanf("%d", &y);
  
  p = y % 4;
  q = y % 100;
  r = y % 400;
  
  if (p = 0) {
    if (q = 0) {
      if (r = 0) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    } else {
      printf("YES\n");
    }
  } else {
    printf("NO\n");
  }
  
  return 0;
}