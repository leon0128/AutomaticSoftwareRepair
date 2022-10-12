#include <stdio.h>
#include <string.h>

int main(){
  char S[100];
  char ch;
  gets(S);
  int n = strlen(S);
  printf("%c\n", S[n/2]);
  return 0;
}