#include <stdio.h>
int main(void){
  int A,B;
  int ans = 0;
  int i;
  
  scanf("%d" , &A);
  scanf("%d" , &B);
  
  if(A / 4 == 1 || B / 4 == 1){
    ans += 4;
  }
  if(A / 2 == 1 || A / 2 == 3 || B / 2 == 1 || B / 2 == 3){
    ans += 2;
  }
  if(A % 2 == 1 || B % 2 == 1){
    ans += 1;
  }
  
  printf("%d" , ans);
  
}