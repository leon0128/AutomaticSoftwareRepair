#include <stdio.h>
int main (void)
{
  int n;
  scanf("%d", &n);
  int a[n];
  int i;
  int ans = 0;
  for (i = 0; i < n; i++)
  {
    scanf("%d", &a[i]);
    ans += a[i];
  }
  printf("%d", ans);
  
  return 0;
}