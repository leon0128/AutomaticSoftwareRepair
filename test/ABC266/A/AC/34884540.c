#include<stdio.h>

void main(){
	int i=0;
	char s[101];
	scanf("%s", &s);
	while (s[i] != '\0') {
		i++;
	}
	int a = (i + 1) / 2 ;
	printf("%c", s[a-1]);
}