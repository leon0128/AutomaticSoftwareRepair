#include <stdio.h>

#define N	5
#define A	100

int main() {
	static char used[A + 1];
	int i, cnt;

	cnt = 0;
	for (i = 0; i < N; i++) {
		int a;

		scanf("%d", &a);
		if (!used[a])
			used[a] = 1, cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}