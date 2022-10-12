#include"stdio.h"
#include"string.h"

int main(){
	char c[10000];
	gets(c);
	int l=strlen(c);
    printf("%c\n",c[l/2]);
    return 0;
} 