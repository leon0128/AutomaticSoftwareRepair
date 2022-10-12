#include <stdio.h>
#include <string.h>

#define N	5

char ss[N][16] = {
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
};

int main() {
	static char s[16];
	int i;

	scanf("%s", s);
	for (i = 0; i < N; i++)
		if (strcmp(ss[i], s) == 0) {
			printf("%d\n", N - i);
			return 0;
		}
	return 0;
}