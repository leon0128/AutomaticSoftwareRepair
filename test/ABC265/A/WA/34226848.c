#include <stdio.h>

int main() {
	int x, y, n, sum = 0;
	scanf("%d %d %d", &x, &y, &n);
	while(n - 3 >= 0) {
		sum += y;
		n -= 3;
		if(n - 3 <= 0) break;
	}
	while(n - 1 >= 0) {
		sum += x;
		n -= 1;
		if(n - 1 <= 0) break;
	}
	printf("%d", sum);
}