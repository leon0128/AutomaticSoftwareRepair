#include<stdio.h>
int main(void){
  int a;
  scanf("%d",&a);
  if(a % 400 == 0){
    printf("YES\n");
  }else if(a % 4 == 0 && a % 100 != 0){
    printf("YES\n");
  }else{
    printf("NO\n");
  }
  return 0;
}
