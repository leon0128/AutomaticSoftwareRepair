#include<stdio.h>
int main(void){
  char s[16];
  scanf("%s",s);
  switch(s[1]){
    case 'o':printf("5");break;
    case 'u':printf("4");break;
    case 'e':printf("3");break;
    case 'h':printf("2");break;
    case 'r':printf("1");break;
  }
  
  return 0;
}