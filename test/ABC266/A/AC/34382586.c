#include <stdio.h>

int main(void)
{
  char s[100]={'\0'};
  int count=0;
  scanf("%s",s);
  for(int i=0;i<100;i++)
    {
      char getchar = s[i];
      if(getchar!='\0')
      {
        count++;
      }
    }
  int calc = count/2;
  char ans = s[calc];
  printf("%c\n",ans);
  }