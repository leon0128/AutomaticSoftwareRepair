#include<stdio.h>
#include<string.h>
int main(){
	char a[10000];
	scanf("%s",&a);
	int s;
	s=strlen(a);
	printf("%c",a[s/2]);
}