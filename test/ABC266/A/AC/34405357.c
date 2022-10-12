#include<stdio.h>
int length(const char s[]){
  int len=0;
  while(s[len])
    len++;
  return len;
}

int main(void){
  char str[99];
  scanf("%s",str);
  printf("%c",str[(length(str)-1)/2]);
  return 0;
}