#include <stdio.h>
int main() {
  int yen;
  int X;
  scanf("%d", &X);
  int Y;
  scanf("%d", &Y);
  int N;
  scanf("%d", &N);
  
if (X<=Y) {
  if (3*X > Y){
   int a = N/3;
    yen = (a*Y) + ((N-a*3)*X);
    printf("%d", yen);
  }
  else if (3*X < Y){
    yen = N*X;
        printf("%d", yen);

  }
  else if (N*X == N*Y){
    printf("%d", N*X);
  }
  }
}
