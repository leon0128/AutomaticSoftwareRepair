#include<string.h>
#include<stdio.h>
int main(void){
  int n;
  char s[100];
  
  gets(s);
  n= strlen(s);
  printf("%c",s[(n+1)/2 -1]);
  return 0;
}