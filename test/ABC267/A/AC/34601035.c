#include <stdio.h>

int return_num(char s[])
{
   if (s[0] == 'M')
      return 5;
   if (s[0] == 'T' && s[1] == 'u')
      return 4;
   if (s[0] == 'W')
      return 3;
   if (s[0] == 'T' && s[1] == 'h')
      return 2;
   if (s[0] == 'F')
      return 1;
}

int main(void)
{
   char s[101];
   scanf("%s", s);
   int ans = return_num(s);
   printf("%d", ans);
   return 0;
}