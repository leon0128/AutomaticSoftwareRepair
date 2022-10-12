#include<stdio.h>
int main(){
  int n;
  scanf("%d",&n);
  printf("%02X\n",n);//10進数の255を16進でFFと表示させるならxは大文字,ffと表示させるならxは小文字
  return 0;
}