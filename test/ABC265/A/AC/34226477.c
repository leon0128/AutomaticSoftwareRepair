#include<stdio.h>
#include<math.h>
int main(void) {
	int X = 0, Y = 0, N = 0,i=0;

	int ans = 0;
	int R1 = 0, R2 = 0;
	scanf("%d %d %d", &X, &Y, &N);
	int X3 = X * 3;
	R1= N / 3;
	R2=  N%3;
	if (X3 <= Y) {
		ans = X3 * R1 + R2 * X;
	}
	else {
		ans = Y * R1 + R2 * X;
	}

	printf("%d",ans);
	


	return 0;
}