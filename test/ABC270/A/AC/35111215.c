#include <stdio.h>

int main(void) {

  int a[2], ans[2][3] = {0}, score = 7;
  scanf("%d %d", &a[0], &a[1]);
  for (int i = 0; i < 2; i++) {
    if (a[i] == 1 || a[i] == 3 || a[i] == 5 || a[i] == 7) {
      ans[i][0] = 1;
    }
    if (a[i] == 2 || a[i] == 3 || a[i] == 6 || a[i] == 7) {
      ans[i][1] = 1;
    }
    if (a[i] == 4 || a[i] == 5 || a[i] == 6 || a[i] == 7) {
      ans[i][2] = 1;
    }
  }
  //printf("%d %d %d\n", ans[0][0], ans[0][1], ans[0][2]);
  //printf("%d %d %d\n", ans[1][0], ans[1][1], ans[1][2]);
  for (int j = 0; j < 3; j++) {
    if (ans[0][j] == 0 && ans[1][j] == 0) {
      //printf("j = %d\n", j);
      if(j == 0) {score -= 1;}
      else if (j == 1) {score -= 2;}
      else if (j == 2) {score -= 4;}
      else {continue;}
    }
  }
  printf("%d\n", score);
  return 0;
}