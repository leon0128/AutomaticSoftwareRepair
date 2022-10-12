//ABC266_A
#include <stdio.h>
#include <string.h>
int main(void){
	int len;
	char s[105]={};
	scanf("%s",&s);
	len=strlen(s);
	printf("%c\n",s[(len/2)]);
	return 0;
}