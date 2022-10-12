#include<stdio.h>
int main(void){
  int N;
  char hai[17] = "0123456789ABCDEF";
  int kari = 0;
  
  scanf("%d" , &N);
  
  kari = N / 16;
  printf("%c" , hai[kari]);
  
  kari = N % 16;
  printf("%c" , hai[kari]);
}