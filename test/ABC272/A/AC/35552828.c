#include <stdio.h>

int main() {
   int n,i,a, sum;
  scanf("%d", &n);
  for (i=0;i<n; i++)
    {
      scanf("%d", &a);
      sum +=a;
    }
  
  printf("%d", sum);
  return 0;
}