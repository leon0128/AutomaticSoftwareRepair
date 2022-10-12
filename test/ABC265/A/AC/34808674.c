#include<stdio.h>
 
void main(){
   int x,y,n,num,money;
   scanf("%d",&x);
   scanf("%d",&y);
   scanf("%d",&n);
   if(3*x<=y){
    money=x*n;
    printf("%d",money);
   }else {
    num=n%3;
    money=(y*(n-num)/3)+x*num;
    printf("%d",money);
   }
   return;
}