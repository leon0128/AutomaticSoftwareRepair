#include <stdio.h>

int main(){
  int X,Y,N,k,a,b;
  scanf("%d %d %d",&X,&Y,&N);
  if (3*X <= Y){
    printf("%d",X*N);
  }else{
    k = 0;
    while (1==1){
      b = X*N - k;
      if (b % (3*X - Y) != 0){
        k++;
        continue;
      }
      b = b / (3*X - Y);
      a = N - 3*b;
      if (a >= 0){
        break;
      }else{
        k = k + 3*X - Y;
        continue;
      }
    }
    printf("%d",X*a + Y*b);
  }
  return 0;
}