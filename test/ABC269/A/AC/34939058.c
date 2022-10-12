#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (void){
	
	char arr[]={"Takahashi"};
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	int s=(a+b)*(c-d);
	printf("%d\n",s);
	printf("%s",arr);
	
}