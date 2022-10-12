#include <stdio.h>
int main(void){
  char S[99];
  int i,N;
  scanf("%s",&S);
  for(i = 0; i < 99; i++){
    if(S[i] == '\0'){
      N = i;
      break;
    }
  }
  printf("%c\n",S[N/2]);
  return 0;
}