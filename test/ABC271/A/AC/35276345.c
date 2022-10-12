#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count;
	char s[16] = "0123456789ABCDEF";
	scanf("%d",&n);
	i = (int)n/16;
	n %= 16;
	printf("%c%c",s[i],s[n]);
	return 0;
}