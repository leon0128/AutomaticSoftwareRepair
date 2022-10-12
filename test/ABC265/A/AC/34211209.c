#include<stdio.h>

int main(){
    int x, y, n, ans1, ans2, res1, res2;
    scanf("%d %d %d", &x, &y, &n);
    if(n >= 3){
        ans1 = n / 3;
        ans2 = n % 3;
        res1 = ans1*y + ans2*x;

        res2 = n * x;
        if(res1 > res2){
            printf("%d", res2);
        }else{
            printf("%d", res1);
        }
    }else{
        printf("%d", n*x);
    }
    return 0;
}