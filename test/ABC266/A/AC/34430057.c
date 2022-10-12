#include <stdio.h>
#include <string.h>

#define N	99

int main() {
	static char cc[N + 1];
	int n;

	scanf("%s", cc), n = strlen(cc);
	printf("%c\n", cc[n / 2]);
	return 0;
}