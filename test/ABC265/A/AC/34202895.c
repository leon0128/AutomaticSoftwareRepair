#include <stdio.h>
int main()
{
  int x, y, n;
  scanf("%d %d %d", &x, &y, &n);
  int ans;
  if(3 * x > y)
    ans = y * (n / 3) + x * (n % 3);
  else
    ans = x * n;
  printf("%d\n", ans);
  return 0;
}