#include<stdio.h>
int main()
{
char s[99];
  gets(s,stdin);
  int i,count=0;
  for(i=0;s[i]!='\0';i++)
            {
             count++;
            }
      printf("%c",s[count/2]);
  return 0;
}