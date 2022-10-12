#include<stdio.h>

int main(){
	int x, y, n;
	int diff = 0;
	int resx = 0, resy = 0;
	int mody = 0;
	int res;
	
	scanf("%d", &x);
	(void)getchar();
	scanf("%d", &y);
	(void)getchar();
	scanf("%d", &n);

	res = n*x;

	mody = n % 3;
	resy = (mody * x) + ((n/3) * y);

	if(resy < res)
		res = resy;
	
	printf("%d\n", res);
	return 0;
}
