#include<stdio.h>
 
int main () {
  int x, y, n;
  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &n);
  if (x * 3 >= y) {
    printf("%d", (n % 3) * x + (n / 3) * y);
  }
  else {
    printf("%d", x * n);
  }
}