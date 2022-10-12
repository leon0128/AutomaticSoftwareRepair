#include<stdio.h>

int main(){
    int a, b, ans = 0;
    scanf("%d %d", &a, &b);

    if(0 < a + b && a + b <= 7){
        ans = a + b;
    }else if (a + b > 7){
        ans = 7;
    }else{
        ans = 0;
    }
    printf("%d", ans);
    return 0;
}