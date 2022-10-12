#include <stdio.h>
#include <math.h>

int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  int a_array[3], b_array[3];
  for(int i = 0; i < 3; i++) {
    a_array[i] = 0;
    b_array[i] = 0;
  }
  if(a >= 4){
    a_array[2] = 1;
    a -= 4;
  }
  if(a >= 2) {
    a_array[1] = 1;
    a-= 2;
  }
  if(a >= 1) {
    a_array[0] = 1;
  }
  if(b >= 4){
    b_array[2] = 1;
    b -= 4;
  }
  if(b >= 2) {
    b_array[1] = 1;
    b-= 2;
  }
  if(b >= 1) {
    b_array[0] = 1;
  }
  int ans = 0;
  for(int i = 0; i < 3; i++) {
    if(a_array[i] + b_array[i] > 0) ans += pow(2,i);
  }
  printf("%d\n", ans);
}