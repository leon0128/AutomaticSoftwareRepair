#include <stdio.h>

int main(void){
  int year;

  scanf("%d\n",&year);
  
  if(year%400 == 0){
    printf("YES\n");
  }
  else if(year%100 == 0){
    printf("NO\n");
  }
  else if(year%4 == 0){
    printf("YES\n");
  }
  else {
    printf("NO\n");
  }

  return 0;
}