#include<stdio.h>
int main() {
  char s[100] = "abcdefg";
  int n = sizeof(s);
  printf("%d\n",s[n/2]);
  return 0;
}