#include<stdio.h>
#include<string.h>
int main(void){
  int a;
  char s[101];
  scanf("%s",s);
  a=strlen(s);
  a=a/2;
  printf("%c",s[a]);
  return 0;
}