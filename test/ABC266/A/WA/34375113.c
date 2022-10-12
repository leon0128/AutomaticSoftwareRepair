#include <stdio.h>
#include <string.h>

int main(void) {
  char s[100];
  scanf("%s", s);
  printf("%c", s[strlen(s)+1]);
  return 0;
}