#include <stdio.h>

int main() {
  char s[100];
  scanf("%s", s);
  int k = 0;
  while(s[k] != '\0') {
    k++;
  }
  printf("%c\n", s[k/2]);
  return 0;
}