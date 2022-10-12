#include<stdio.h>
#include<string.h>
 
int main(void){
  char S[100];
  scanf("%s",S);
  printf("%c", S[(strlen(S))/2]);
  return 0;
}