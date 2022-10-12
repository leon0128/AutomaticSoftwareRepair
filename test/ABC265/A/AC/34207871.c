#include <stdio.h>

int main(void)
{
  int x, y, n, m, ans = 0;;
  
  scanf("%d %d %d", &x, &y, &n);
  
  if (3 * x <= y)
    ans = x * n;
  else
  {
    m = n / 3;
    ans = y * m;
    if (n % 3 != 0)
      ans += x * (n % 3);
  }
  
  printf("%d\n", ans);
  
  return (0);
}