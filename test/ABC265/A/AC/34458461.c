#include <stdio.h>
int main(void)
{
   int x, y, n, a, ans, cnt, i;
   scanf("%d%d%d", &x, &y, &n);

   if (n < 3 || y > 3 * x)
   {
      printf("%d", x * n);
      return 0;
   }
   else
   {
      a = (n / 3) * y;
      ans = (n % 3) * x + a;
   }
   printf("%d", ans);
   return 0;
}