#include <stdio.h>
#include <string.h>
int main(void){

	char s[100];
	scanf("%s",s);
	size_t leng;
	leng=strlen(s);
	printf("%c\n",s[((leng+1)/2)-1]);
	return 0;
}
