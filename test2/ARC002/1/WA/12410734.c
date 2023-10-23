#include <stdio.h>

int main(void)
{
	int year;
	char *uru = "NO";

	printf("1. ");
	scanf("%d", &year);

	if ((year % 4) == 0)
		uru = "YES";
	if ((year % 100) == 0)
		uru = "NO";
	if ((year % 400) == 0)
		uru = "YES";

	printf("1. %s\n", uru);

}
