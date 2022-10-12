#include<stdio.h>
#include<string.h>
#include<math.h>

int main (void){
	char arr[100]={0};
	scanf("%s",arr);
	
	if(strcmp(arr,"Monday")==0){
		printf("%d",5);
	}else if(strcmp(arr,"Tuesday")==0){
		printf("%d",4);
	}else if(strcmp(arr,"Wednesday")==0){
		printf("%d",3);
	}else if(strcmp(arr,"Thursday")==0){
		printf("%d",2);
	}else if(strcmp(arr,"Friday ")==0){
		printf("%d",1);
	}
}