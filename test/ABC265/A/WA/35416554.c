#include <stdio.h>

int main() {
	int x, y, n;
	scanf("%d %d %d", &x, &y, &n);

	if (3 * x > y) {
		printf("%d", x * (n / 3) + y * (n % 3));
	}
	if (3 * x < y) {
		printf("%d", x * n);
	}

}