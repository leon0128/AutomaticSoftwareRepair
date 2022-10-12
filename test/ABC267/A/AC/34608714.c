/* A - Saturday */

#include <stdio.h>
#include <string.h>

int main(void){
  char s[10];
  scanf("%s", s);
  if(strcmp(s, "Monday") == 0) printf("%d\n", 5);
  else if(strcmp(s, "Tuesday") == 0) printf("%d\n", 4);
  else if(strcmp(s, "Wednesday") == 0) printf("%d\n", 3);
  else if(strcmp(s, "Thursday") == 0) printf("%d\n", 2);
  else if(strcmp(s, "Friday") == 0) printf("%d\n", 1);
  else fprintf(stderr, "unexpected input value: %s", s);
  return 0;
}