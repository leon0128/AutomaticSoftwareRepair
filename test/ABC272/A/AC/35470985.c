#include<stdio.h>

int main(void){
	int N;
  scanf("%d", &N);
  int ans = 0, tmp;
  for(int i = 0; i < N; i++){
  	scanf("%d", &tmp);
    ans += tmp;
  }
  printf("%d", ans);
}