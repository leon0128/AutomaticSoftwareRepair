#include <stdio.h>
#include <string.h>
int main() {
  int N;
  char S[100];
  scanf("%s", &S);
  N = strlen(S);

  printf("%c", S[N / 2]);
  return 0;
}