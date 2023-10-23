#include <stdio.h>
#include <math.h>

int daysofmonth (double a2, double b2) {
  int days, b = (int)b2, a = (int)a2;
  switch (b) {
    case 4:
    case 6:
    case 9:
    case 11:
      days = 30;
      break;
    case 2:
      if (a % 4 == 0) days = 29;
      if (a % 100 == 0) days = 28;
      if (a % 400 == 0) days = 29;
      break;
    default:
      days = 31;
      break;
  }
  return days;
}

int isDivide (double a, double b, double c, int n) {
  double x = a / b;
  if (x - floor(x) != 0) return 0;
  if ((x / c) - floor(x) == 0 && n == 1) { 
    printf("%d/%02d/%02d\n", (int)a, (int)b, (int)c); 
    return 1;
  } 
  return 0;
}

int main() {
  double y,m,d;

  scanf("%lf/%lf/%lf", &y, &m, &d);
  
  while (1) {
    while (d <= daysofmonth(y, m)) {
      if (isDivide(y, m, d, 1) == 1) break;
      d++;
    } 
    if (isDivide(y, m, d, 0) == 1) break;
    m++;
    
    if (m == 13) { 
      printf("%d/01/01\n", (int)y + 1);
      break;
    }
    d = 1;
  }
  
  return 0;
}
