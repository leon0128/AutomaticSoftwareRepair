#include<stdio.h>
#include<stdlib.h>
int main (void)
{
  int X=0,Y=0,Z=0,kyo;
  scanf("%d %d %d",&X,&Y,&Z);
  if(X>Y&&Y<Z)kyo=-1;
  else if(Y>Z)kyo=abs(X)+abs(Y)+abs(Z);
  else kyo=X; 
  printf("%d",kyo);
  return 0;
}
  