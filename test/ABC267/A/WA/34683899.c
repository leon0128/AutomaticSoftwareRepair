#include <stdio.h>

int main(void){
  char S[10];
  scanf("%s",S);
//  printf("%s",S);
//   Monday, Tuesday, Wednesday, Thursday, Friday
  if(S=="Monday"){
    return 5;
  }else if(S=="Tuesday"){
    return 4;
  }else if(S=="Wednesday"){
    return 3;
  }else if(S=="Thursday"){
    return 2;
  }else if(S=="Friday"){
    return 1;
  }
  return 0;

}