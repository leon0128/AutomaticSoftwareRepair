#include<stdio.h>
#include<string.h>
int main() {
  char s[100] = "abcdefg";
  int n = strlen(s);
  printf("%d\n",s[n/2]);
  return 0;
}