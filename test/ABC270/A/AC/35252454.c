#include <stdio.h>

int main(void){
  int a[3][8] = {{0,1,0,1,0,1,0,1},{0,0,1,1,0,0,1,1},{0,0,0,0,1,1,1,1}};
  int b[3];
  int A = 0;
  int B = 0;
  int answer = 0;
  
  scanf("%d", &A);
  scanf("%d", &B);
  
  for(int i = 0; i < 3; i++){
    if(a[i][A] == 0 && a[i][B] == 0){
      b[i] = 0;
    } else if(a[i][A] == 1 || a[i][B] == 1) {
      b[i] = 1;
    }
  }
  
  for(int j = 0; j < 8; j++){
    if(a[0][j] == b[0] && a[1][j] == b[1] && a[2][j] == b[2]){
      answer = j;
      break;
    }
  }
  
  printf("%d", answer);
  
  return 0;
}