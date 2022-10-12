#include<stdio.h>
int main(void){
  int n;
  scanf("%d",&n);
  char s[]="0123456789ABCDEF";
  printf("%c%c",s[n/16],s[n%16]);
  return 0;
}