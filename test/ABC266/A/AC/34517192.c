#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}


int main(void)
{
	char str[99];
	scanf("%s", str);

	int len = 0;
	len = ft_strlen(str);
	if (len % 2 == 0)
      len = len / 2 + 1;
  	else
      len = len / 2;
	printf("%c", str[len]);
}
