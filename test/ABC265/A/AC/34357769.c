#include <stdio.h>

int main()
{
    int X = 0;
    int Y = 0;
    int N = 0;

    scanf("%d %d %d", &X, &Y, &N);

    int money = 0;
    if(N <= 2){
        money = X * N;
    }else{
        if(3*X <= Y){
            money = money + X*N;
        }else{
            while(N >= 3){
                money += Y;
                N -= 3;
            }
            if(N != 0){
                money = money + X*N;
            }
        }
    }

    printf("%d\n", money);

    return 0;
}
