#include<stdio.h>

int main(void){
  
  int a,b,x;
  
  scanf("%d",&x);
  a = x%16;
  x = x/16;
  b = x%16;
  
  char str[16] = "0123456789ABCDEF";
  printf("%c%c",str[a],str[b]);
  
  return 0;
}
