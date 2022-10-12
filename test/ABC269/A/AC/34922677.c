#include <stdio.h>
int main(void)
{
  int a,b,c,d,answer = 0;

  scanf("%d %d %d %d",&a,&b,&c,&d);
  answer = (a + b)*(c - d);

  printf("%d\n",answer);
  printf("Takahashi");

  return 0;
}
