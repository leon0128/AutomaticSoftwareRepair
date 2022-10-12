#include <stdio.h>
#include <string.h>

char s[107];

int main(){
	int len;
	scanf("%s", &s[1]);
	len = strlen(&s[1]);
	printf("%c", s[(len + 1) / 2]);
	return 0;
}