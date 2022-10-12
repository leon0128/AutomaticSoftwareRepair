#include <stdbool.h>
#include <stdio.h>
#define false 0
#define true 1

void judge(int score, int *is_solved) {
  for (int i = 0; i < 3; i++) {
  	is_solved[i] = false;
  }
    switch (score) {
    case 0:
      break;
    case 1:
      is_solved[0] = true;
      break;
    case 2:
      is_solved[1] = true;
      break;
    case 4:
      is_solved[2] = true;
      break;
    case 3:
      is_solved[0] = is_solved[1] = true;
      break;
    case 5:
      is_solved[0] = is_solved[2] = true;
      break;
    case 6:
      is_solved[1] = is_solved[2] = true;
      break;
    case 8:
      is_solved[0] = is_solved[1] = is_solved[2] = true;
      break;
  }
}

int main(int argc, char **argv) {
  int takahashi_solved[] = {0, 0, 0};
  int aoki_solved[] = {0, 0, 0};
  int sunuke_solved[] = {0, 0, 0};
  
  int takahashi_score;
  int aoki_score;
  
  scanf("%d %d", &takahashi_score, &aoki_score);
  
  judge(takahashi_score, takahashi_solved);
  judge(aoki_score, aoki_solved);
  
  #if 0
  for (int i = 0; i < 3; i++) {
  	printf("%d ", takahashi_solved[i]);
  }
  printf("\n");
  for (int i = 0; i < 3; i++) {
  	printf("%d ", sunuke_solved[i]);
  }
  printf("\n");
  #endif
  
  for (int i = 0; i < 3; i++) {
  	if (takahashi_solved[i] == false && aoki_solved[i] == false) {
    	sunuke_solved[i] = false;
    } else {
    	sunuke_solved[i] = true;
    }
  }
  
  #if 0
  for (int i = 0; i < 3; i++) {
  	printf("%d ", sunuke_solved[i]);
  }
  printf("\n");
  #endif
  
  int ans = 0;
  if (sunuke_solved[0] == true)
    ans += 1;
  if (sunuke_solved[1] == true)
    ans += 2;
  if (sunuke_solved[2] == true)
    ans += 4;
  
  printf("%d", ans);
}