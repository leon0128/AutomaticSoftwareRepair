#include<stdio.h>
#include<string.h>
int main(void) {
	int num = 0;
	char str[100];
	
	
	scanf("%s", str);
	num = strlen(str);
	printf("%c",str[((num+1)/2)-1]);

	return 0;
}