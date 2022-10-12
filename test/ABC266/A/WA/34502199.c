#include<stdio.h>
#include<string.h>
int main() {
  char s[100];
  scanf("%c",&s);
  int n = strlen(s);
  printf("%c\n",s[n/2]);
  return 0;
}