#include<stdio.h>
int main(){
	int x,y,z;
	scanf("%d %d %d",&x,&y,&z);
	if (3*x<=y){
		printf("%d",x*z);
	}
	else{
		printf("%d",((z/3)*y)+(x*(z%3)));
	}
}