#include <stdio.h>

int main () {
  char s[100] = "";
  
  int res = 0;
  
  int len = 0;
  
  res = scanf("%s", s);
  while (s[len] != '\0') {
    len++;
  }
  
  printf("%c\n", s[len/2]);
  return 0;
}