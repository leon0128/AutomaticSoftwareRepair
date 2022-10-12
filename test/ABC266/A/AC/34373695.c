#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int main(){
	
	char s[100];
	int x;
	
	gets(s);
	
	x = strlen(s);
	
	printf("%c",s[(x-1)/2]);
	
}