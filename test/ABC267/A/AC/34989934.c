#include<stdio.h>
int main(void){
  char s[10];
  scanf("%s",s);
  if(s[1]=='o')printf("5");
  if(s[1]=='u')printf("4");
  if(s[1]=='e')printf("3");
  if(s[1]=='h')printf("2");
  if(s[1]=='r')printf("1");
  return 0;
}