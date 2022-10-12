#include<stdio.h>

int main(){
  int a,b,c;
  scanf("%d",&a);
  scanf("%d",&b);
  
  int t1 = 0,t2 = 0,t3 = 0;
  if((a-4)>=0){
    t1 = 1;
    a = a - 4;
  }
  if((a-2) >= 0){
    t2 = 1;
    a = a - 2;
  }
  if((a-1) >= 0){
    t3 = 1;
    a = a - 1;
  }
  if((b-4)>=0){
    t1 = 1;
    b = b - 4;
  }
  if((b-2) >= 0){
    t2 = 1;
    b = b - 2;
  }
  if((b-1) >= 0){
    t3 = 1;
    b = b - 1;
  }
  c = t1*4 + t2*2 + t3*1;
  printf("%d",c);
}