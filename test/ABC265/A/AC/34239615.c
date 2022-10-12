#include<stdio.h>

int main()
{
  int x,y,n;
  scanf("%d%d%d",&x,&y,&n);
  if(3*x>y)
  {
    int a = ((n/3)*y + x*(n%3));
    printf("%d\n",a);
  }
  else{
    printf("%d\n",x*n);
  }
}