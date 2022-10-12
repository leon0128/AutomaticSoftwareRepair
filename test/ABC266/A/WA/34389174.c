#include<stdio.h>
int main()
{
char s[99];
  fgets(s,99,stdin);
  int i,count=0;
  for(i=0;s[i]!='\0';i++)
            {
             count++;
            }
      printf("%d",s[count/2]);
  return 0;
}