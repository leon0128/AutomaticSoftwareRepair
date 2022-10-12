#include<stdio.h>

void main(){
   int x,y,n,num,money;
   printf("Set apple's price\n");
   scanf("%d",&x);
   scanf("%d",&y);
   printf("How many apples do you want ?\n");
   scanf("%d",&n);
   if(3*x<=y){
    money=x*n;
    printf("The money you need to buy is %d yen.\n",money);
   }else {
    num=n%3;
    money=(y*(n-num)/3)+x*num;
    printf("The money you need to buy is %d yen.\n",money);
   }
   return;
}