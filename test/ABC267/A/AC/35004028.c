#include<stdio.h>

int	main(void)
{
	int N;
	char S[10];

	scanf("%s", S);
	if (S[0] == 'M')
		printf("5\n");
	else if(S[0] == 'T')
	{
		if (S[1] == 'u')
			printf("4\n");
		else
			printf("2\n");
	}
	else if(S[0] == 'W')
		printf("3\n");
	else
		printf("1\n");
	return (0);
}
