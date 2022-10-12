#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count;
	char s[100];

	scanf("%s",s);

	n = strlen(s);

	printf("%c",s[(int)(n/2)]);

	return 0;

}