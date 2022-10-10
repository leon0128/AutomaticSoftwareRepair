#include <stdio.h>

int main(void)
{
  int n;
  scanf("%d", &n);
  int sum = 0;
  for(int i = 0; i < n; i++) {
    int tmp = 0;
    scanf("%d", &tmp);
    sum += tmp;
  }
  
  printf("%d\n", sum);
  return 0;
}