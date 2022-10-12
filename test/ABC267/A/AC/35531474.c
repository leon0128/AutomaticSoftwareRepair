#include<stdio.h>
#include<string.h>
int main(){
	char S[10];
    scanf("%s", S);
	if(!strcmp(S, "Monday")){
        printf("5");
	}else if(!strcmp(S, "Tuesday")){
		printf("4");
	}else if(!strcmp(S, "Wednesday")){
		printf("3");
	}else if(!strcmp(S, "Thursday")){
		printf("2");
	}else{
		printf("1");
	}
	return 0;
}