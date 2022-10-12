#include <stdio.h>

int main () {
  int a_e = 0;
  
  int res = 0;
  
  int app[101] = {};
  int ans = 0;
  
  for (int i = 0; i < 5; i++) {
    res = scanf("%d", &a_e);
    app[a_e] = 1;
  }
  
  for (int i = 0; i <= 100; i++) {
    ans += app[i];
  }
  
  printf("%d\n", ans);
  return 0;
}