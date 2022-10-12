#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[100000000]={0};
int main(){
	int n,x,y;
	scanf("%d%d%d",&x,&y,&n);
	int sum=0;
	if(y>3*x)sum=n*x;
	else 
		sum=n/3*y+n%3*x;
	printf("%d",sum);
    return 0;
}