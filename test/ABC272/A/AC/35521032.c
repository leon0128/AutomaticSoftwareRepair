#include<stdio.h>
int main() {
  int n, sum = 0;
  scanf("%d", &n);
  while(n--) {
    int a;
    scanf("%d", &a);
    sum += a;
  }
  printf("%d\n", sum);
  return 0;
}