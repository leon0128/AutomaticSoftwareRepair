#include <stdio.h>

int main()
{
  char s[20];
  int x;
  scanf("%s",s);
  if(s[0]=='M')
      x=5;
  else if(s[0]=='W')
      x=3;
  else if(s[0]=='F')
      x=1;
  else if(s[1]=='h')
      x=2;
  else
      x=4;
  
  printf("%d",x);
  return 0;
}