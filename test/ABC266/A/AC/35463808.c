#include<stdio.h>

int main(){
  
  char str[100];
  int i;
  
  scanf("%s",&str);
  
  for(i = 0; str[i] != '\0'; i++);
  
  printf("%c",str[(i+1)/2-1]);
}