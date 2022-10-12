#include <stdio.h>
#include <string.h>
int main (void)
{
	char S[100];
	scanf("%s",S);
	if (!strcmp(S, "Friday"))
		printf("%d\n", 1);
	else if (!strcmp(S, "Thursday"))
		printf("%d\n", 2);
	else if (!strcmp(S, "Wednesday"))
		printf("%d\n", 3);
	else if (!strcmp(S, "Tuesday"))
		printf("%d\n", 4);
	else //(!strcmp(S, "Monday"))
		printf("%d\n", 5);
	return 0;
}
