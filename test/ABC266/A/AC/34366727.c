#include <stdio.h>

int main()
{
	char S[101];
	scanf("%s", S);

	int i;
	for (i = 0; S[i] != 0; i++);
	printf("%c\n", S[i/2]);
	fflush(stdout);
	return 0;
}