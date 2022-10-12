#include<stdio.h>
int main(void)
{
  int n;

  scanf("%d",&n);

  if(n<17)
    printf("0%X",n);
  else
    printf("%X",n);

  return 0;

}
