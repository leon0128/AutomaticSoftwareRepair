#include <stdio.h>
int main(){
  char s[99];
  scanf("%s", s);
  int T = strlen(s);
  int a = (T+1)/2;
  printf("%c", s[a-1]);
  return 0;
  }