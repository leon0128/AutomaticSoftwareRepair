#include <stdio.h>
#include <string.h>

int main(void) {
	char S[1024];
	if (scanf("%1023s", S) != 1) return 1;
	putchar(S[strlen(S) / 2]);
	putchar('\n');
	return 0;
}
