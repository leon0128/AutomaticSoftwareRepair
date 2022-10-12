#include<stdio.h>
int main(void)
{
  int takahashi=0;
  int aoki=0;
  int sunuke=0;
  int a=0;
  int b=0;
  int d=0;
  
  scanf("%d ",&takahashi);
  scanf("%d",&aoki);
  if(takahashi>=4)
  {
    sunuke+=4;
    takahashi-=4;
    a=1;
  }
  if(takahashi>=2)
  {
    sunuke+=2;
    takahashi-=2;
    b=1;
  }
  if(takahashi>=1)
  {
    sunuke+=1;
    takahashi-=1;
    
    d=1;
  }
  
  if(aoki>=4)
  {
     aoki-=4;
     if(a!=1)
     {
     sunuke+=4;
     }
    
  }
  if(aoki>=2)
  {
      aoki-=2;
     if(b!=1)
     {
     sunuke+=2;
     }
    
  }
  if(aoki>=1)
  {
      aoki-=1;
     if(d!=1)
     {
     sunuke+=1;
     }
    

  }
  printf("%d",sunuke);
  
  return 0;
}
