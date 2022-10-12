#include <stdio.h>
#pragma warning (disable:4996)
#include <stdlib.h>

int main() {
	int a, b, c, d, sum;

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);
	scanf("%d", &d);

	sum = (a + b) * (c - d);

	printf("%d\n", sum);
	printf("Takahashi");
}