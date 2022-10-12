#include <stdio.h>

int main (void){

  char str[100];
  int i = 0;
  
  scanf("%s", str);
  
  while(str[i] != 0){
	i++;    
  }
  
  printf("%c", str[i / 2]);
  
  
  
  
  return 0;
  
}