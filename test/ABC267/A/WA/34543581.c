#include <stdio.h>
#include<string.h>
int main(){
    char s[100];
    scanf("%s",&s);
    if(strcmp(s,"Monday")==0){
        printf("5\n");
    }else if(strcmp(s,"Thuesday")==0){
        printf("4\n");
    }else if(strcmp(s,"Wednesday")==0){
        printf("3\n");
    }else if(strcmp(s,"Thursday")==0){
        printf("2\n");
    }else if(strcmp(s,"Friday")==0){
        printf("1\n");
    }
	return 0;
}