#include <stdio.h>
#include <string.h>

static char	g_str[100];

int	main(void)
{
	int	len;
	int	mid;

	scanf("%s", g_str);
	len = strlen(g_str);
	mid = len / 2;
	printf("%c\n", g_str[mid]);
	return (0);
}
