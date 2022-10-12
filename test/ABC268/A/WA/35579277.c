#include <stdio.h>
int i;

int main() {
	int a[5], n, j;

	for ( n = 0; n < 5; n++) {

		scanf("%d", &a[n]);
	}

//	printf("%d", a[2]);

	if (a[0] >= 0 && a[0] <= 100 && a[1] >= 0 && a[1] <= 100 && a[2] >= 0 && a[2] <= 100 && a[3] >= 0 && a[3] <= 100
	        && a[4] >= 0 && a[4] <= 100) {
		i = 5;

		for (n = 0; n < 2; n++) {

			for (j = n + 1; j < 4; j++) {

				if (a[n] == a[j]) {
					i--;
				}
			}
		}

		printf("%d", i);
	}

	return 0;
}
