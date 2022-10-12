#include <stdio.h>
int main(void){
  int A[5];
  int ans = 0;
  int i,j;
  int count;
  
  for(i = 0; i < 5; i++){
    scanf("%d" , &A[i]);
    for(j = 0,count = 0; j <= i; j++){
      if(A[i] == A[j]){
        count++;
      }
    }
    if(count == 1){
        ans++;
    }
  }
  
  printf("%d" , ans);
}