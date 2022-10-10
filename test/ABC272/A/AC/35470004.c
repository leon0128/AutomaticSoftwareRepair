#include <stdio.h>
int main()
{
  int n, ans = 0, i;
  scanf("%d", &n);
  for(i = 0; i < n; i++){
    int a;
    scanf("%d", &a);
    ans += a;
  }
  printf("%d\n", ans);
  return 0;
}