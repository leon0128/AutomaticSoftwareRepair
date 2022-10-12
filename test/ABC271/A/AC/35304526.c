#include <stdio.h>
int main(void) {
  int i=0,j=0;
  int num;
  char henkan[16] = "0123456789ABCDEF";
  char answer[10];

  scanf("%d",&num);
  if(num<16){
  printf("0");
    if(num==0){
      printf("0");
    }
  }
  while(num > 0) {
    j = num % 16;
    num = num / 16;
    answer[i] = henkan[j];
    i++;
  }
  i--;

  for(j=i; j>=0; j--) {
    printf("%c",answer[j]);
  }
  return 0;
}