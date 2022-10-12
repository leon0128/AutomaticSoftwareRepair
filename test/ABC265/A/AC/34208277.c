#include <stdio.h>

int main() {
	
	int X, Y, N, i, sum, min = 100000, tmp = 0;
	
	scanf("%3d %3d %3d", &X, &Y, &N);
	
	tmp = N;
	
	sum = tmp / 3 * Y;
	tmp %= 3;
	sum += tmp * X;
	
	if(sum < min) min = sum;
	
	sum = N * X;
	
	if(sum < min) min = sum;
	
	
	printf("%d", min);
	
	return 0;
}