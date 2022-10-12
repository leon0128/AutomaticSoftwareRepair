#include <stdio.h>

int main()
{
	int i, ans = 0, A, num[101] = {};
	for (i = 0; i < 5; i++) {
		scanf("%d", &A);
		num[A]++;
	}
	for (i = 0; i <= 100; i++) if (num[i] > 0) ans++;
	printf("%d\n", ans);
	fflush(stdout);
	return 0;
}