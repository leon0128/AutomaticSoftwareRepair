#include<stdio.h>
#include<string.h>
int main(void){
  char S[99];
  int T,a;
  scanf("%s",S);
  T=strlen(S);
  a=((T+1)/2)-1;
  printf("%c",S[a]);
  return 0;
}
