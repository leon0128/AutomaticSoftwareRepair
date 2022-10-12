#include<stdio.h>

int main()
{
  char s[101];
  scanf("%s",s);
  int i=0;
  int count=0;
  while(s[i]>0)
  {i++;
   count=count+1;
  }
  
  printf("%c",s[count/2]);
  return 0;
}
