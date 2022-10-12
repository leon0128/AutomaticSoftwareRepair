#include<stdio.h>

int main(){
    int a, b, ans = 0;
    scanf("%d %d", &a, &b);

    if(a != b && a + b <= 7){
        ans = a + b;
    }else if (a != b && a + b > 7){
        ans = 7;
    }else if(a == b && a + b <= 7){
        ans = a;
    }else{
        ans = 7;
    }
    printf("%d", ans);
    return 0;
}