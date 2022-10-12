#include <stdio.h>
#include <string.h>
 
int	main()
{
  char	str[100];
  int	m;
  
  scanf("%s", str);
  m = strlen(str) / 2;
  printf("%c", str[m]);
}