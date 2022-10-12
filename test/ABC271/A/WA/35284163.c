#include <stdio.h>

int main(void) {
  
  int x;
  char genbun[16] = "0123456789ABCDEF";
  char ans[10];
  int i = 0;
  int j = 0;
  scanf("%d",&x);

  while(x > 0) {
   
    j = x % 16;
    x = x / 16;
    ans[i] = genbun[j];
    i++;
  }

  i--;
  
  for(int j=i; j>=0; j--) {
    printf("%c",ans[j]);
  }
  
  return 0;
}