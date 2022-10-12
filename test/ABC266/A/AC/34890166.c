#include<stdio.h>
void main(void){
  char s[100];
  int size;
  scanf("%s",s);
  size = strlen(s);
  printf("%c",s[(size+2)/2-1]);
}