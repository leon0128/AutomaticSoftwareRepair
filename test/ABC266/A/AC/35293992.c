#include <stdio.h>
#include <string.h>

int main()
{
	char S[100];
	int N;
	int M;

	scanf("%s", S);

	N = strlen(S);

	M = (N+1) / 2 - 1;

	printf("%c\n", S[M]);

	return 0;
}
