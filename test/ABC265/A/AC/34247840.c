#include <stdio.h>

int min(int a, int b) { return a < b ? a : b; }

int main() {
	int x, y, n;

	scanf("%d%d%d", &x, &y, &n);
	printf("%d\n", n / 3 * min(y, x * 3) + n % 3 * x);
	return 0;
}