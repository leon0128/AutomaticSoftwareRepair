#include<stdio.h>
#include<stdbool.h>
int main() {
  int y;
  scanf("%d", &y);
  bool flag = false;
  if(y % 4 == 0) flag = true;
  if(y % 100 == 0) flag = false;
  if(y % 400 == 0) flag = true;
  if(flag) printf("YES\n");
  else printf("NO\n");
  return 0;
}