#include <stdio.h>

int main(void) {
  int Y, judge = 0;

  scanf("%d", &Y);

  if(Y % 4 == 0){
    judge = 1;
  }
  if(Y % 100 == 0){
    judge = 0;
  }
  if(Y % 400 == 0){
    judge = 1;
  }
  if(judge == 1){
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}