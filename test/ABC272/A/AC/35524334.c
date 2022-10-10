#include<stdio.h>

int sumf(int t[], int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += t[i];
	}
	return sum;
}

int main() {
	
	int n, a[101];

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	printf("%d\n", sumf(a, n));

	return 0;
}