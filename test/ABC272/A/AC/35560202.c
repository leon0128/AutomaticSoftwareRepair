#include <stdio.h> 
#include <stdlib.h>


int main() {
  int n;
  int i;
  int sum = 0;
  int *a;
  scanf("%d", &n);
  a = malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  free(a);
  printf("%d", sum);
  return 0;
}