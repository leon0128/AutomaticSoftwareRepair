#include <stdio.h>

int main(void)
{
	int in, isLeap = 0;
	scanf("%d", &in);
	if (!(in % 400)) {
		++isLeap;
	} else if (!(in % 4)) {
		if (in % 100)
			++isLeap;
	}
	if (isLeap)
		puts("YES");
	else
		puts("NO");
	return 0;
}
