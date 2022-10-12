#include <stdio.h>
#include <limits.h>

int min(int a[], int n) {
	int i, min;

	min = a[0];
	for (i = 0; i < n; i++) {
		if (a[i] < min) min = a[i];
	}

	return min;
}

int main(void) {
	int x, y, n;
	int price[100];
	int i, j, k;

	for (i = 0; i < 100; i++) price[i] = INT_MAX;

	scanf("%d %d %d", &x, &y, &n);

	k = 0;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= n; j++) {
			
			if (i + 3 * j == n) {
				price[k] = x * i + y * j;
				k++;
			}

		}
	}

	printf("%d\n", min(price, 100));

	return 0;
}