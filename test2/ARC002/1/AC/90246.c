#include <stdio.h>

int main(){
  int y;

  scanf("%d",&y);

  if(!(y%4) && (!(y%400) || y%100)){
    printf("YES\n");
  }else{
    printf("NO\n");
  }

  return 0;
}