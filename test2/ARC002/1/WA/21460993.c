#include<stdio.h>
int main(void){
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
        printf("YES");
    }else{
        printf("NO");
    }
    return 0;
}