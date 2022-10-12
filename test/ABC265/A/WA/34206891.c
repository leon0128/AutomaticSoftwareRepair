#include<stdio.h>
 
int main () {
  int x, y, n;
  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &n);
  printf("%d", (n % 3) * x + y);
}