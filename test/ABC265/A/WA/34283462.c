#include<stdio.h>
int main(){
  int X, Y, N, amari;
  scanf("%d%*c%d%*c%d", &X, &Y, &N);
  if(N<3||3*X<Y){
	printf("%d",X*N);
  }
  else{
	amari = Y%3;
    printf("%d",amari*X+(N-amari)*Y);
  }
  return 0;
}