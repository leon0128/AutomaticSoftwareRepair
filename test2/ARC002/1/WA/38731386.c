#include <stdio.h>
int main() {
  int a;
  scanf("%d", &a);
  if (a%4==0)
    if(a%100==0)
      if(a%400==0)
        printf("YES");
      else
        printf("NO");
    else
      printf("YES");
  else
    printf("NO");
}