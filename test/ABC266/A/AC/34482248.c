#include <stdio.h>
#include <string.h>
int main (void)
{
  	int a,len;
	char s[99]={'\0'};
  	scanf("%s",s);
  	len = strlen(s);
  	a = len/2;
  	printf("%c",s[a]);
}