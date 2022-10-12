#include<stdio.h>
#include<string.h>
int main(){
 
  char s[100];
  scanf("%s",s);
  int l=strlen(s);
  
  printf("%c",s[(l/2)]);
  return 0;
}
