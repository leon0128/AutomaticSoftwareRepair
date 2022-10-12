#include <stdio.h>

int main(void)
{
  char a[10];
  scanf("%[^n]s",a);
  if(a=='Monday')
    printf("5\n");
  if(a=='Tuesday')
    printf("4\n");
  if(a=='Wednesday')
    printf("3\n");
  if(a=='Thursday')
    printf("2\n");
  if(a=='Friday')
    printf("1\n");
  if(a=='Saturday')
    printf("0\n");
  if(a=='Sunday')
    printf("6\n");
  return 0;
}