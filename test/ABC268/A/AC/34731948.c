#include <stdio.h>
int main(void)
{
   int x, i;
   int a[1000] = {0};
   int cnt = 0;

   for (i = 0; i < 5; i++)
   {
      scanf("%d", &x);

      a[x] = 1;
   }

   for (i = 0; i <= 100; i++)
   {
      if (a[i] == 1)
         cnt++;
   }
   printf("%d", cnt);
   return 0;
}