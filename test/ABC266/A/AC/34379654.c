#include<stdio.h>
#include<string.h>

int main (void){
	
	char arr[100]={0};
	scanf("%s",&arr);
	
	int l=strlen(arr);
	int p=l/2;
	//printf("%d",p);
	printf("%c",arr[p]);
}