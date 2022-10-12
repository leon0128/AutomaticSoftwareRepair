#include<stdio.h>
#include<string.h> 
char s[1000010];
int main(){
 	scanf("%s",s);
 	putchar(s[(strlen(s)+1) /2-1]);
 	return 0;
 }