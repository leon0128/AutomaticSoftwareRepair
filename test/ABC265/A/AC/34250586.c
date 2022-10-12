#include<stdio.h>

int main(){
	int x,y,n,a,b,c,d,e,f;
	scanf("%d %d %d",&x,&y,&n);
	b = 0;
	a = n;
	c = 0;
	d = 0;
	e = 0;
	if(3*x<y||n<3){
		printf("%d",x*n);
		return 0;
	}
	else{
		a = n % 3;
		b = n / 3;
		c = y * b;
		e = x * a;
		printf("%d",c+e);
		return 0;
	}
	return 0;
}