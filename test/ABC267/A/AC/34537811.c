#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[10];
  
  scanf("%s", str);
  
  if (strcmp(str, "Monday") == 0)
    printf("5\n");
  else if (strcmp(str, "Tuesday") == 0)
    printf("4\n");
  else if (strcmp(str, "Wednesday") == 0)
    printf("3\n");
  else if (strcmp(str, "Thursday") == 0)
    printf("2\n");
  else if (strcmp(str, "Friday") == 0)
    printf("1\n");
  
  return (0);
}