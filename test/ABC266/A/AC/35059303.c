#include<stdio.h>
#include<string.h>
int main(void) {
	char s[99] = {0};
	scanf("%s",s);
	int n = strlen(s);
	n /= 2;
	printf("%c",s[n]);
	return 0;
}