#include <stdio.h>
int main(void){
  int i;
  int A;
  int ans = 0;
  int N = 0;
  
  scanf("%d" , &N);
  for(i = 0; i < N; i++){
    scanf("%d" , &A);
    ans += A;
  }
  printf("%d" , ans);
}