#include <stdio.h>
#include <string.h>

int main ( void ){
	int n;
	scanf("%d",&n);
	char s[17];
	strcpy(s,"0123456789ABCDEF");
	char s1 = s[n/16];
	char s2 = s[n%16];
	printf("%c%c\n",s1,s2);
	return 0;
}