#include <stdio.h>

int main(void)
{
  int Y, flag = 0;
  scanf("%d", &Y);

  if (Y % 4 == 0) {
    flag = 1;
    if (Y % 100 == 0) {
      flag = 0;
      if (Y % 400 == 0) {
        flag = 1;
      }
    }
  }

  if (flag == 1) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}
