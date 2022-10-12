#include <stdio.h>
int main(void){
  int a[4];
  int i;
  
  for(i = 0; i < 4; i++){
    scanf("%d" , &a[i]);
  }
  
  printf("%d\n" , (a[0]+a[1])*(a[2]-a[3]));
  printf("Takahashi");
}