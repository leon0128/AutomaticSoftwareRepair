#include<stdio.h>
int main(void)
{
  int n;
  int flg=0;
  
  scanf("%d",&n);
  if(n%4==0){
    flg=1;
    if(n%100==0){
      flg=0;
    }
    if(n%400==0){
      flg=1;
    }
  }
  if(flg==1){
    printf("YES\n");
  }else{
    printf("NO\n");
  }
  return 0;
}