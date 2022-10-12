#include<stdio.h>
#include<stdlib.h>


int main(){
  char s[100];scanf("%s",s);
  int i=0;
  while(s[i]!='\0'){
    i++;
  }
  int len_str;
  len_str=i;
  printf("%c",s[(len_str-1)/2]);
  return 0;
}