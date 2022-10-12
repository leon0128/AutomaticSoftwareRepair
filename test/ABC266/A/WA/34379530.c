#include<stdio.h>
#include<string.h>
int main()
{
  char str[1001];
  scanf("%s",str);
  int l=strlen(str);
  printf("%c",l/2);
}