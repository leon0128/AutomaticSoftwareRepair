#include<stdio.h>
#include<string.h>

void main(){
  
  char a[110];
  int len;
  
  scanf("%s\n", a );
  len = strlen( a );
  printf("%c\n", a[len/2] );
  return ;
}
