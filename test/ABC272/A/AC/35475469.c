#include <stdio.h>

int main(void)
{
  int n;
  int a;
  int sum = 0;
  int i;
  
  scanf("%d",&n);
  for (i = 0; i < n; i++){
    scanf("%d",&a);
    sum  += a;
  }
  printf("%d",sum);
  return 0;
}