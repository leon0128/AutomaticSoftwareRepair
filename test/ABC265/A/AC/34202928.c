#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n,x,y;
	int count;

	scanf("%d %d %d",&x,&y,&n);
	if(3*x <= y){
		printf("%d",x*n);
	}
	else{
		printf("%d",(int)(n/3)*y+(n%3)*x);
	}

	return 0;
}
