#include<stdio.h>

#define NUM 998244353

int main(){
  
  int n;
  scanf("%d",&n);
  
  int x=0;
  while((n-x)%NUM != 0)
    x++;
  
  printf("%d",x);
}