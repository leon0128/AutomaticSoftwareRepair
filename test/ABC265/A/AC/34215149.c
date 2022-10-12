#include<stdio.h>
int main(void){
  int X,Y,N,Z,a,b,c;
  scanf("%d %d %d",&X,&Y,&N);
  if(X*3>Y){
    a=N%3;
    b=N/3;
    a=X*a;
    b=Y*b;
    printf("%d",a+b);
  }else{
    a=N*X;
    printf("%d",a);
  }
  return 0;
}