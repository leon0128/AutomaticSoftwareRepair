#include<stdio.h>
#include<stdlib.h>

int main(void){
  int Y;//入力

  if(scanf("%d", &Y) < 1)
    exit(1);

  if( Y < 1000 || Y > 2999)
    exit(1);

  if( Y % 4 != 0 ){
    printf("NO\n");
  }else if( Y % 4 == 0 && Y % 100 != 0){
    printf("YES\n");
  }else if( Y % 4 == 0 && Y % 100 == 0 && Y % 400 != 0){
    printf("NO\n");
  }else{
    printf("YES\n");
  }

  return 0;
}
