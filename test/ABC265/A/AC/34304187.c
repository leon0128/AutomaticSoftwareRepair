#include<stdio.h>
int main() {
	int x, y, z;
	int i, sum = 0;
	scanf("%d %d %d", &x, &y, &z);
	if (x * 3 >= y) {
		for (i = z; i >= 3; i = i - 3) {
			sum = sum + y;
		}sum = sum + i * x;
	}
	else sum = z * x;
	printf("%d", sum);
	return 0;
}