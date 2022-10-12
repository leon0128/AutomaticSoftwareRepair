#include <stdio.h>
#include <stdlib.h>

int main() {

	int x, y, z = 0;

	scanf("%d%d%d", &x, &y, &z);

	if (abs(x) <= abs(y)){
		printf("%d", abs(x));
	}
	else if (abs(x) > abs(y)) {
		if (x * y < 0) {
			if (abs(z) <= abs(y)) {
				if (y * z < 0) {
					printf("%d", abs(x - z) + abs(z));
				}
				else if (y * z > 0) {
					printf("%d", abs(x));
				}
			}
			else if (abs(z) > abs(y)) {
				if (y * z < 0) {
					printf("%d", abs(x - z) + abs(z));
				}
				else if (y * z > 0) {
					printf("-1");
				}
			}
		}
	}

	return 0;
}