#include <stdio.h>

int main()
{
  int n, i, a, s;

  scanf("%d", &n);
  s = 0;
  for( i = 0; i < n; i++ )
  {
    scanf("%d ", &a);
    s += a;
  }
  printf("%d\n", s);
  return 0;
}
