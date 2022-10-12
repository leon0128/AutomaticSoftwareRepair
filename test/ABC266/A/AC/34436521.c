#include<stdio.h>
#include <string.h>

int main(void)
{
  char s[99];
  int len;
  
  scanf("%s",s);

  len = strlen(s);

  len = len / 2;

  printf("%c\n",s[len]);

  return 0;
}
