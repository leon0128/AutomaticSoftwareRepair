#include <stdio.h>
#include <string.h>

int main () {
  char s[10] = "";
  
  int res = 0;
  
  int ans = 0;
  char t[5][10] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
  
  res = scanf("%s", s);
  for (int i = 0; i < 5; i++) {
    if (strcmp(s, t[i]) == 0) {
      ans = 5-i;
    }
  }
  
  printf("%d\n", ans);
  return 0;
}