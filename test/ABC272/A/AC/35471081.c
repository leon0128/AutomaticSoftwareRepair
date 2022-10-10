#include <stdio.h>
int main(void){
  int N, A, S=0;
  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d", &A);
    S+=A;
  }
  printf("%d\n", S);
  return 0;
}