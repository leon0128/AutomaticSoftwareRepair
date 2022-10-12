#include<stdio.h>
#include<string.h>
int main()
{
  char s[100];
  scanf("%s",s);
  int d=strlen(s);
  printf("%c",s[d/2]);
  return 0;
}
