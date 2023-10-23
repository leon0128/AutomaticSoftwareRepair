#include <stdio.h>

int main(void) {

  int y;
  scanf("%d", &y);
  int leap;
  if (y%4 == 0) {
    leap = 1;
    if (y%100 == 0) {
      leap = 0;
      if (y%400 == 0) {
        leap = 1;
      }
    }
  } else {
    leap = 0;
  }
  if (leap == 1) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}