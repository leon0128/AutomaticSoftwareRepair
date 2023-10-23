#include<stdio.h>
int main(){
  int n;
  scanf("%d",&n);
  if(n % 400 < 1){
    printf("YES\n");
  }else if(n % 100 < 1){
    printf("NO\n");
  }else if(n % 4 < 1){
    printf("YES\n");
  }else{
    printf("NO\n");
  }
  return 0;
}