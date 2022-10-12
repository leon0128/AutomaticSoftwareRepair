#include<stdio.h>
int main(){
  int n;
  scanf("%d",&n);
  if(n<16){
    printf("%d",0);
  }
  printf("%x\n",n);
  return 0;
}