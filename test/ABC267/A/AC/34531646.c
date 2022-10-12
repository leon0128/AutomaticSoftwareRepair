#include<stdio.h>
int main()
{
	char s[32];
	scanf("%s", s);
	int ans;
	if (s[1] == 'o')
		ans = 5;
	else if (s[1] == 'u')
		ans = 4;
	else if (s[1] == 'e')
		ans = 3;
	else if (s[1] == 'h')
		ans = 2;
	else
		ans = 1;
	printf("%d\n", ans);
	return 0;
}