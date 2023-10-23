#include<stdio.h>
int main(void){
    int n;
    int m=0;
    scanf("%d",&n);
    if(n%4==0&&n%100!=0){
        m=1;
    }if(n%400==0){
        m=1;
    }if(m==1){
        printf("Yes");
    }else{
        printf("No");
    }
    return 0;
}