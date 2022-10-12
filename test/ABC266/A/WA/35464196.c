#include<stdio.h>

#define NUM 998244353

int main(){
  
  long long int n,x=0;
  
  scanf("%d",&n);
  
  while((n-x)/NUM != 0)
    x++;
  
  printf("%d",x);
}