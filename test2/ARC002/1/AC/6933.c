#include <stdio.h>

int main() {
  
  int year = 0;
  int n = 0;
  scanf("%d", &year);
  
  if (year % 4 == 0) {
    n = 1;
  }
  
  if (year % 100 == 0) {
    n = 0;
  }
  
  if (year % 400 == 0) {
    n = 1;
  }
  
  if (n == 1) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}