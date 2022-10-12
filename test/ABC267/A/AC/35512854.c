#include <string.h>
#include <stdio.h>
int main(){
	char str[10];
	char a1[10]="Monday";
	char a2[10]="Tuesday";
	char a3[10]="Wednesday";
	char a4[10]="Thursday";
	char a5[10]="Friday";
	
	scanf("%s",&str);
	if(strcmp(str,a1)==0) printf("5");
	if(strcmp(str,a2)==0) printf("4");
	if(strcmp(str,a3)==0) printf("3");
	if(strcmp(str,a4)==0) printf("2");
	if(strcmp(str,a5)==0) printf("1");
	return 0;
}