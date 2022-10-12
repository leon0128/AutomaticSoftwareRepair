#include <stdio.h>

int main(void){
  int n;
  scanf("%d", &n);

  char c1, c2;
  if(n % 16 < 10)
    c2 = '0' + (n % 16);
  else
    c2 = 'A' + (n % 16 - 10);

  n /= 16;
  if(n % 16 < 10)
    c1 = '0' + (n % 16);
  else
    c1 = 'A' + (n % 16 - 10);

  printf("%c%c\n", c1, c2);
  
  return 0;
}