#include<stdio.h>

int main(void){
  char S[10];
  scanf("%s",&S);
  if(S[1]=='o'){ printf("5");}
  else if(S[1]=='u'){ printf("4");}
  else if(S[1]=='e'){ printf("3");}
  else if(S[1]=='h'){ printf("2");}
  else{ printf("1");}
  return 0;
}