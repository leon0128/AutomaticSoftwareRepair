#include<stdio.h>
#include<string.h>
int main(void)
{
  int i,x,ind;
  char S[100];
  scanf("%s",S);
  i=strlen(S);
  ind=(i-1)/2;
  printf("%c",S[ind]);
  return 0;
}