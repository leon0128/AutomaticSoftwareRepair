#include <stdio.h>
int main()
{
  int n;
  char a, b;
  scanf("%d", &n);
  if(n % 16 >= 10) b = 'A' + (n % 16) - 10;
  else b = '0' + (n % 16);
  n /= 16;
  if(n % 16 >= 10) a = 'A' + (n % 16) - 10;
  else a = '0' + (n % 16);
  printf("%c%c\n", a, b);
  return 0;
}