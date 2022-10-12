#include <stdio.h>

int main(){
  int n,a,cnt=0;
  char flag[101] = {};
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    scanf("%d", &a);
    if (flag[a] == 0) cnt++;
    flag[a] = 1;
  }
  printf("%d\n", cnt);
}