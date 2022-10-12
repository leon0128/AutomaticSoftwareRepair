#include <stdio.h>
 
int main() {
  int a, b, c = 0;
  scanf("%d %d", &a, &b);
  int x1, x2, x3, y1, y2, y3;
  x1 = a % 2;
  x2 = ((a - x1) % 4) / 2;
  x3 = (a - x1 - 2 * x2) / 4;
  y1 = b % 2;
  y2 = ((b - y1) % 4) / 2;
  y3 = (b - y1 - 2 * y2) / 4;
  
  c = (x1 || y1) + (x2 || y2) * 2 + (x3 || y3) * 4;
  printf("%d", c);
  return 0;
}