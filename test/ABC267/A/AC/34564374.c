#include<stdio.h> 
#include<string.h>
int main(){
	char S[20];
	int x;
	gets(S);
	if(strcmp(S,"Monday")==0)
		x=1; 
	else if(strcmp(S,"Tuesday")==0)
		x=2; 
	else if(strcmp(S,"Wednesday")==0)
		x=3; 
	else if(strcmp(S,"Thursday")==0)
		x=4; 
	else
		x=5; 
	x=6-x;
	printf("%d",x);
  return 0;
}
