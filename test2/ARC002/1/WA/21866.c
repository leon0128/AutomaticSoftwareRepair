#include<stdio.h>

int main(){
	
	int y;
	
	scanf("%d",&y);
	
	if( y%400 == 0){
		printf("yes\n");
	}
	
	else if(y%100 == 0){
		printf("no\n");
	}
	
	else if(y % 4 == 0){
		printf("yes\n");
	}
	
	else{
		printf("no\n");
	}
	
	return 0;
	
}