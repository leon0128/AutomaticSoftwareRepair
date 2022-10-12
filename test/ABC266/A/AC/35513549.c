#include <string.h>
#include <stdio.h>
int main(){
	char str[100];
	scanf("%s",&str);
	int len=strlen(str);
	int i=(len+1)/2;
	printf("%c",str[i-1]);
	return 0;
}