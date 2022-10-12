#include<stdio.h>
int main()
{
  int X,Y,N;
  scanf("%d %d %d", &X,&Y,&N);
  
  int ansY=0;
  int min=100000000;
  int i;
  for(i=0;i<=N;i++)
  {
    int tmp=X*(N-i)+Y*i/3;
    //printf("%d\n",i);
    if(tmp<=min && (i%3==0))
    {
      ansY = i;
      min = tmp;
    }
  }
  
  printf("%d",min);
  
  return 0;
}