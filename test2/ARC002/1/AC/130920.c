#include <stdio.h>

int main(void)
{
  int Y, a = 0;
  scanf("%d", &Y);
  if(Y % 4 == 0)
    a = 1;
  if(Y % 100 == 0)
    a = 0;
  if(Y % 400 == 0)
    a = 1;
  if(a == 1) printf("YES\n");
  if(a == 0) printf("NO\n");
  return 0;
}