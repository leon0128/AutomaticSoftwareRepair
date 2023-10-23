#include<stdio.h>

int main(){
	int f=0,n;
	scanf("%d",&n);
	if(n%4==0)f=1;
	if(n%100==0)f=0;
	if(n%400==0)f=1;
	if(f==1)puts("YES");
	else puts("NO");
	return 0;
}