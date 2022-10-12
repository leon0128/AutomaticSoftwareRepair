#include <stdio.h>

int main(void)
{
  int i;
  char str[100];
  
  scanf("%s", str);
  
  for(i=0; str[i]!='\0'; ++i);
  
  printf("%c\n", str[i / 2]);
  
  return (0);
}