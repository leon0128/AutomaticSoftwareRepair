#include<stdio.h>
#include<string.h> 
char s[1000010];
int main(){
 	gets(s);
 	putchar(s[(strlen(s)+1) /2]);
 	return 0;
 }