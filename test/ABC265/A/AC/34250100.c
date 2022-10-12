#include <stdio.h>

int main(){
  int x, y, n;
  scanf("%d %d %d", &x, &y, &n);
  if(x * 3 < y){
    printf("%d", x * n);
  }else{
    printf("%d", n / 3 * y + x * (n%3));
  }
  return 0;
}