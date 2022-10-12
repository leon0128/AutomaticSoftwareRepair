#include <stdio.h>
#include <string.h>

int main(void){
	char day[256];
	gets(day);
	
	if(strcmp(day,"Monday") == 0){
		puts("5");
	}
	else if(strcmp(day,"Tuesday") == 0){
		puts("4");
	}
	else if(strcmp(day,"Wednesday") == 0){
		puts("3");
	}
	else if(strcmp(day,"Thursday") == 0){
		puts("2");
	}
	else if(strcmp(day,"Friday") == 0){
		puts("1");
	}
	
	return 0;
}