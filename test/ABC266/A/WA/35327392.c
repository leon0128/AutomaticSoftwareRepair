#include<stdio.h>
#include<stdlib.h>

int main(){
  char S[99];
  scanf("%s",S);
  
  int count=0;
  
  for(int i=0;i<99;i++){
    if(S[i]!='\0'){
      break;
    }
    count++;
  }
  
  int middle=count/2+1;
  
  printf("%c",S[middle]);
  
  return 0;
}