#include <stdio.h>

int main(void){
  int n;
  scanf("%d", &n);
  int a;
  int ans = 0;
  for(int i = 0; i < n; ++i){
    scanf("%d", &a);
    ans += a;
  }

  printf("%d", ans);

  return 0;
}