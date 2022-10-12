#include<stdio.h>
int main()
  {
  int X,Y,N,cx=0,cy=0;
  if(!scanf("%d %d %d",&X,&Y,&N)){return 1;}
  if(3*X<Y){return !printf("%d",X*N);}
  printf("%d",Y*(N/3)+X*(N%3));
  }