#include<stdio.h>
#include<string.h>

int main(){
	int i;
	char s[262144];
	scanf("%s",s);
	i = strlen(s);
	i/=2;
	printf("%c",s[i]);
}