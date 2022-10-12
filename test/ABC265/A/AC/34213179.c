#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
int main(void){
int N,X,Y;
int a,b;
scanf("%d %d %d",&X,&Y,&N);

int sum=0;
if(3*X>Y && 3<=N){
  a=N/3;
  b=N%3;
  sum=a*Y+b*X;
  printf("%d",sum);
}

if(3*X<Y || N<3){
  sum=X*N;
  printf("%d",sum);
}


 return 0;
}