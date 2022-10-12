//ABC265_A
#include <stdio.h>
#include <limits.h>
int main(void){
	int x,y,n;
	int tmp=0,a=0,b=0;
	int ans=0;
	scanf("%d %d %d",&x,&y,&n);
	a=n/3*y; b=(n%3)*x; tmp=a+b;
//	printf("a:%d b:%d tmp:%d\n",a,b,tmp);
	printf("%d",(int)fmin(tmp,(x*n)));
	return 0;
}