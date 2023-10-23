#include<stdio.h>
int main(){
    int a,b=1;
    scanf("%d",&a);
    if(a%4==0){
        b=0;
    }
  if(a%100==0){
        b=1;
    }
    if(a%400==0){
        b=0;
    }
    if(b==0){
        printf("1. YES");
    }else{
        printf("1. NO");
    }
    return 0;
}