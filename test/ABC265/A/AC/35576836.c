#include <stdio.h>
#include <stdlib.h>



int x, y, n;

int main () {
	scanf ("%d %d %d", &x, &y, &n);
	if (x * 3 <= y) {
		printf ("%d", x * n);
	} else {
		printf ("%d", n / 3 * y + (n % 3) * x);
	}
	return 0;
}
