#include<stdio.h>
#include<string.h>

int main (void){
	
	int x,y,n;
	scanf("%d %d %d",&x,&y,&n);
	
	if(3*x < y){
		
		printf("%d",n*x);
		
	}else{
		
		int a=n/3;
		int b=n%3;
		
		printf("%d",a*y+b*x);
	}
}