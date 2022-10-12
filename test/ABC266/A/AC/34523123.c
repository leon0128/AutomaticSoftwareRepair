#include <stdio.h>
#include <string.h>

int main(void)
{
   int n;
   char s[100];
   scanf("%s", s);
   n = strlen(s);
   printf("%c", s[n / 2]);
   return 0;
}
