#include <stdio.h>
#include <string.h>
int main(void){
  char st[99];
  scanf("%s", st);
  int i = strlen(st);
  printf("%c", st[(i+1)/2-1]);
  return 0;
}