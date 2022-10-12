#include<stdio.h>
 
int main(){
  
  char S[]="atcoder";
  
  int i;
  
  for(i = 0; S[i] != '\0'; i++);
  
  printf("%c",S[i/2+1]);
}
