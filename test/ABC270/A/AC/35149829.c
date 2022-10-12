#include <stdio.h>

int main()
{
  int a,b,c,s1 = 0,s2 = 0,s3 = 0;
  scanf("%d %d",&a,&b);
  if(a==5||b==5)
  {
    s1 = 1;
    s3 = 1;
  }
  if(a==3||b==3)
  {
    s1 = 1;
    s2 = 1;
  }
  if(a==1||b==1)
  {
    s1 = 1;
  }
  if(a==6||b==6)
  {
	s2 = 1;
    s3 = 1;
  }
  if(a==2||b==2)
  {
    s2 = 1;
  }
  if(a==4||b==4)
  {
	s3 = 1;
  }
  if(a==7||b==7)
  {
    s1 = 1;
    s2 = 1;
    s3 = 1;
  }
  c = s1 + 2*s2 + 4*s3;
  printf("%d",c);
  
  return 0;
}