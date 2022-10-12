#include<stdio.h>
#include<string.h>
int main()
{
	char str[100];
    int len;
    gets(str); 
    len=strlen(str);
	printf("%c\n",str[len/2]);
	
}