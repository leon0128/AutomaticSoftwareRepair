#include <stdio.h>

int main()
{
	char S[101];
	scanf("%s", S);

	if (S[0] == 'M') printf("5\n");
	else if (S[0] == 'W') printf("3\n");
	else if (S[0] == 'F') printf("1\n");
	else if (S[1] == 'h') printf("2\n");
	else if (S[1] == 'u') printf("4\n");
	fflush(stdout);
	return 0;
}