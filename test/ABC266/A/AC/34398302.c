#include<stdio.h>

int main()
{
   int l,y;
char s[100];
gets(s);
l=strlen(s);
y=(l)/2;
printf("%c",s[y]);
}