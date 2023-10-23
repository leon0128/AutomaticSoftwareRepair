#include<stdio.h>
int main(){
  int y,ans=0;
  scanf("%d",&y);
  if(y%4==0){
    ans=1;
    if(y%100==0 && y%400!=0)ans=0;
  }
  puts(ans?"YES":"NO");
}