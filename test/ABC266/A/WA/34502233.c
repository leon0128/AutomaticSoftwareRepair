#include<stdio.h>
#include<string.h>
int main() {
  char str[99];
  scanf("%c",&str);
  int len;
  len = strlen(str);
  printf("%c\n",str[len/2]);
  return 0;
}