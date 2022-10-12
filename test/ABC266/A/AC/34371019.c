#include<stdio.h>
int main(void){
  char s[100];
  scanf("%s",s);
  int cou=0;
  for(cou=0;cou<100;cou++){
   if(!s[cou]) break; 
  }
  printf("%c",s[(cou-1)/2]);
  
  return 0;
}