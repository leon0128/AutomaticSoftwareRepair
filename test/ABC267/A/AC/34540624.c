#include <stdio.h>

int main(void)
{
  char day[10];
  scanf("%s", day);
  
  if (day[1] == 'o') printf("5");
  if (day[1] == 'u') printf("4");
  if (day[1] == 'e') printf("3");
  if (day[1] == 'h') printf("2");
  if (day[1] == 'r') printf("1");
  
  return 0;
}