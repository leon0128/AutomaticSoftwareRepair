#include <stdio.h>

int main(){
  int init[5];
  for(int i = 0; i < 5; i++) {
    scanf("%d", &init[i]);
  }
  int array[5];
  int min, num;
  for(int i = 0; i < 5; i++) {
    min = init[0];
    num = 0;
    for(int j = 0; j < 5; j++) {
      if(min > init[j]) {
        min = init[j];
        num = j;
      }
    }
    array[i] = min;
    init[num] = 101;
  }
  int ans = 5;
  for(int i = 0; i < 4; i++) {
    if(array[i] == array[i+1]) ans--;
  }
  printf("%d\n", ans);
  return 0;
}