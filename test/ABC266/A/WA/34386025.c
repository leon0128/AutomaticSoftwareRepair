#include<stdio.h>
#include<string.h>
int main()
{
  int  n,i=0,p=0;
  scanf("%d",&n);
  for(;i>0;i++);
  {
    if(((n-i)%998244353==0)&& p==0)
    {
      printf("%d",i);
      p=1;
    }
  }
}
