#include<stdio.h>
int main(void)
{
  char S[100];
  int T;
  scanf("%s",S);
  T=strlen(S);
  
  
  printf("%c",S[(T-1)/2]);
}